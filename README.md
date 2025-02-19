# Philosophers Project

## Overview
The **Philosophers** project is part of the 42 Network curriculum. It is a concurrency-based challenge that simulates the famous **Dining Philosophers Problem** using threads and synchronization mechanisms in C. The goal is to manage multiple philosophers eating, thinking, and sleeping without encountering deadlocks or race conditions.

## Features
- Multithreaded simulation of philosophers.
- Correct handling of shared resources (forks) using mutexes.
- Prevention of deadlocks and race conditions.
- Real-time lifecycle simulation of philosophers.

## Compilation
To compile the project, use:
```sh
make
```
This will generate the `philosophers` executable.

## Usage
Run the program with the following syntax:
```sh
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
- **number_of_philosophers**: Total number of philosophers (and forks).
- **time_to_die**: Time (in milliseconds) a philosopher can live without eating.
- **time_to_eat**: Time (in milliseconds) a philosopher takes to eat.
- **time_to_sleep**: Time (in milliseconds) a philosopher sleeps after eating.
- **number_of_times_each_philosopher_must_eat** *(optional)*: If specified, the simulation stops when each philosopher has eaten this many times.

## Example
```sh
./philosophers 5 800 200 200
```
This runs a simulation with 5 philosophers, each having 800ms before starving, 200ms to eat, and 200ms to sleep.

## Implementation Details
- Uses **pthreads** for multithreading.
- **Mutexes** are used to prevent concurrent access to forks.
- Ensures proper synchronization to avoid deadlocks.
- Uses precise time management to simulate real-time execution.

## Notes
- If **number_of_philosophers** is 1, the philosopher will starve because they have only one fork.
- If any philosopher does not eat within **time_to_die**, the simulation ends.
- Ensure the input values are valid to avoid undefined behavior.

## Debugging
- Run with Valgrind to check for memory leaks:
  ```sh
  valgrind --tool=helgrind -s ./philosophers 5 800 200 200
  valgrind --leak-check=full --track-origins=yes ./philosophers 5 800 200 200
  ```


## License
This project follows the 42 Network guidelines and is intended for educational purposes.

