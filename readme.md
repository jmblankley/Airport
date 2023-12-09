# Airport Simulation

**Author:** Joshua M. Blankley
**Date:** 11/4/2023

## Project Description

This is a simulation of an airport meant to further the understanding of semaphores and threads.

The AirportAnimator class was provided. My work was done in the myAirport file using semaphores and threads to sync the runway and ensure no collisions or deadlock.

## Technologies Used

This project was built using C++ in an Ubuntu VM as well as Linux Mint (Native).

## Installation

To install this program:

1. Navigate to the source code directory.
2. Type `make` into the termial to produce a file called `fly`.

## Usage

Run `fly` by typing `./fly` in the terminal, followed by a number representing the total number of people in the airport then a number representing the total number of tours needed to be completed.

## Example

`./fly <airport population> <tour requirement>`

The program then uses ncurses to then draw the simulation inside of the terminal.

## Development Log

- Created pseudocode for the program.
- Developed a Plane class and a Flights class.
- Realized the initial approach was overcomplicated, so restructured the project and removed the previously built classes.
- Implemented a function that uses semaphores to manage critical sections (when a plane is on the runway).
- Added counters to track tours completed and airport population.
- Added error messages for tour requirements and airport population mismatches.

## Project 2 Quetions

1. Try running your program with only 11 passengers. What happens? Why?
   - When ran with 11 passengers the program ends because of deadlock. Meaning that each plane is waiting to continue to the next status. But since each plane is filled at random intervals no plane ever (in my testing, but might be possible for one plane to get all passengers) gets 12 passengers. Our for loop will not let any plane "TAXI" until it has 12 passengers. So no plane ever reaches the next status, resulting in deadlock.
2. Try running your program with 12 passengers. What happens? Why?
   - A similar thing happens with 12 passengers. Since the planes are filled randomly the chances of one plane getting all 12 passengers available from the airport is next to zero, no plane ever reaches it critical section, resulting in deadlock.
3. Try running your program with 50 passengers and 100 tours. What happens? why?
   - We have 8 planes (threads), each plane needs 12 passengers to take off. If we evenly spread our 50 passengers between the 8 planes you get appoximately 6.25 passengers per plane. In this scenario no plane gets to its 12 passengers needed to continue on to "TAXI" in turn causing deadlock.
4. Try running your program with 100 passengers and 20 tours. What happens? Why?
   - The program runs smoothly but never reaches 20 tours. Each tour needs 12 passengers and to reach 20 tours you would need 12 multiplied by 20 which is 240 passengers. Given 100 passengers you will never reach 20 tours.
5. What is the minimum number of passengers that will guarantee avoidance of
   deadlock? Why?
   - 97 passengers guarantee avoidance of deadlock. With 8 planes needing 12 passengers to make a trip you need a minimum of 96 passengers to ensure all planes have enough passengers to make a trip and avoid deadlock.
