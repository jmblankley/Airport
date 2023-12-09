/*
Author: jmblankley

Date: October 2023

Purpose: The program is designed to simulate airport operations with multiple planes using threads. It employs semaphores for runway synchronization, allowing planes to perform activities such as takeoff, touring, and landing concurrently. The simulation concludes when the specified airport population is exhausted.
*/

#include "AirportAnimator.hpp"
#include <unistd.h>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <sys/sem.h>
#include <sys/shm.h>

using namespace std;

#define NUM_SEMS 8
#define NUM_PLANES 8

key_t semKey = 42;
int sem_id;

int tourMax;
int airportPop;
int tourCount = 0;

void *startTheDay(void *arg)
{
	while (airportPop > 0)
	{
		int *planeNum = (int *)arg;

		for (int passenger = 1; passenger <= 12; passenger++)
		{

			AirportAnimator::updatePassengers(*planeNum, passenger);
			airportPop--;
			sleep(rand() % 3);
			if (airportPop <= 0)
			{
				return nullptr;
			}
		}

		AirportAnimator::updateStatus(*planeNum, "TAXI");
		AirportAnimator::taxiOut(*planeNum);

		// semwait to see if another plane is on the runway
		struct sembuf command[1];
		command[0].sem_num = 0;
		command[0].sem_op = -1;
		command[0].sem_flg = 0;
		semop(sem_id, command, 1);

		// START CRITICAL SECTION
		AirportAnimator::updateStatus(*planeNum, "TKOFF");
		AirportAnimator::takeoff(*planeNum);
		// END CRITICAL SECTION

		// semsignal the "tower" to let it know the runway is empty
		command[0].sem_num = 0;
		command[0].sem_op = 1;
		command[0].sem_flg = 0;
		semop(sem_id, command, 1);

		AirportAnimator::updateStatus(*planeNum, "TOUR");
		sleep(15 + rand() % 13);

		// semwait to see if another plane is on the runway
		AirportAnimator::updateStatus(*planeNum, "LNDRQ");
		sleep(2);

		command[0].sem_num = 0;
		command[0].sem_op = -1;
		command[0].sem_flg = 0;
		semop(sem_id, command, 1);

		AirportAnimator::updateStatus(*planeNum, "LAND");
		AirportAnimator::land(*planeNum);

		command[0].sem_num = 0;
		command[0].sem_op = 1;
		command[0].sem_flg = 0;
		semop(sem_id, command, 1);

		// semsignal to tower that the runway is clear
		AirportAnimator::updateStatus(*planeNum, "TAXI");
		AirportAnimator::taxiIn(*planeNum);

		AirportAnimator::updateStatus(*planeNum, "DEPLN");
		for (int passenger = 11; passenger >= 0; passenger--)
		{
			AirportAnimator::updatePassengers(*planeNum, passenger);
			sleep(1);
		}
		AirportAnimator::updateStatus(*planeNum, "BOARD");

		tourCount++;
		AirportAnimator::updateTours(tourCount);

		if (airportPop <= 0)
		{
			break;
		}
	}

	return nullptr;
}

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		cerr << "USAGE: " << argv[0] << " <airport population> <max number of tours>" << endl;
		return 1;
	}
	else
	{
		airportPop = atoi(argv[1]);
		tourMax = atoi(argv[2]);

		AirportAnimator::init();

		sem_id = semget(semKey, NUM_SEMS, IPC_CREAT | 0666);
		if (sem_id == -1)
		{
			cerr << "semget() failed with errno =  " << errno << endl;
		}

		// set inital semaphore value to 1 (so they can get on the runway!!)
		int initialSemaphoreValue = 1;

		struct sembuf semaphoreOperation;
		semaphoreOperation.sem_num = 0;
		semaphoreOperation.sem_op = 0;
		semaphoreOperation.sem_flg = 0;

		// Set the initial semaphore value to 1
		if (semctl(sem_id, 0, SETVAL, initialSemaphoreValue) == -1)
		{
			cerr << "semctl() failed with errno = " << errno << endl;
		}

		pthread_t threads[8];

		for (int i = 0; i < 8; i++)
		{
			int *id = new int(i);
			int errCode = pthread_create(&threads[i], nullptr, startTheDay, id);
			if (errCode == -1)
			{
				cerr << "pthreadcreate() failed" << endl;
			}
		}

		for (int i = 0; i < 8; i++)
		{
			pthread_join(threads[i], nullptr);
		}

		AirportAnimator::end();
	}

	return 0;
}
