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
