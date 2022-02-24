# dining_philosophers
A small project to learn the basics of threading a process and resource sharing. On the basis of the "dining philosophers problem", originally formulated by Edsger Dijkstra. Inspired by the "42 Coding School" exercise "philosophers" (February 2022).

## Table of contents
* [Introduction](#introduction)
  * [Allowed functions](#allowed-functions)
  * [Description](#description)
  * [Arguments](#arguments)
* [Approach](#approach)
* [Prerequisites](#prerequisites)
* [How to launch](#how-to-launch)
* [Example](#example)
* [Notes](#notes)

## Introduction

### Allowed functions
memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

### Description
The aim of the exercise is to write a program which does a simulation of the dining philosophers. The situation is as follows:
One or more philosophers sit around a round table. Each philosopher has their own place at the table with a plate and a fork on its right-hand side.

The dish served is a very difficult kind of spaghetti, that has to be eaten with two forks. To achieve this the philosophers have to also use the fork of their neighbor. As a consequence philosophers sitting next to each other can not eat simultaneously.

The philosophers are alternatively eating, sleeping or thinking. When a philosopher has finished eating, they put the forks back on the table and start sleeping. Once awake, they start thinking. The simulation stops when a philosopher dies of starvation. This should be avoided. However philosophers don’t speak with each other and don’t know if another philosopher is about to die.

_Illustration[^1] of the dining philosophers problem_:
![grafik](https://user-images.githubusercontent.com/80413516/154969574-e0201e98-c453-4f77-9eba-93da381f5783.png)
[^1]: From Wikipedia: https://en.wikipedia.org/wiki/Dining_philosophers_problem

#### General Rules
* Global variables are forbidden.
* Each philosopher has a number ranging from 1 to "number_of_philosophers".
* Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
* Any state change of a philosopher must be formatted as follows (with "X" as the number of the philosopher and "timestamp_in_ms" as current timestamp in milliseconds):
  * timestamp_in_ms X has taken a fork
  * timestamp_in_ms X is eating
  * timestamp_in_ms X is sleeping
  * timestamp_in_ms X is thinking
  * timestamp_in_ms X died
* A displayed state message should not be mixed up with another message.
* A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
* Each philosopher should be a thread.

#### Arguments
The program should take the following arguments:
```
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
* _number_of_philosophers_: The number of philosophers and also the number of forks.
* _time_to_die_: The time (in milliseconds) since the beginning of the last meal or the beginning of the simulation, after which a philosopher will die of starvation. 
* _time_to_eat_: The time (in milliseconds) it takes for a philosopher to eat. During that time, they will need to hold two forks.
* _time_to_sleep_: The time a philosopher will spend sleeping.
* _number_of_times_each_philosopher_must_eat_: This argument is optional. If all philosophers have eaten at least "number_of_times_each_philosopher_must_eat" times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## Approach
Here I will explain, how I approached the problem.

## Prerequisites
* gcc
* pthread (```$ sudo apt-get install libpthread-stubs0-dev```)


## How to launch
Compile the program via the Makefile by using ```$ make``` in the root directory of the repository.

Run it like this:

```
$ ./philo 4 800 200 200
```
For a description of the arguments see: [Arguments](#arguments).


## Example
Terminal output for the following examples:

* __Example 1__ _"2 120 60 60 2"_: The program stops after both philosophers ate at least two times.
* __Example 2__ _"2 800 600 300"_: A philosopher dies because at 800, when he should eat again to not die, he is stimm sleeping.
* __Example 3__ _"4 400 200 200"_: Nobody dies and no limit is set.

| __Example 1__ | __Example 2__ | __Example 3__ |
| :---- | :---- | :---- |
| ![Philosphers1](https://user-images.githubusercontent.com/80413516/155484192-e887fb65-a58b-445a-b8cb-93df346184a7.gif) | ![Philosphers2](https://user-images.githubusercontent.com/80413516/155485691-d0efe8bb-9e02-4f41-a716-44b1d0a2a6a5.gif) | ![Philosphers3](https://user-images.githubusercontent.com/80413516/155485700-f430e75f-c312-4b41-86bd-c2aa6fb8d71a.gif) |

## Notes
Depending on the performance of the Computer philosphers may die (faster) on slower computers, but live on faster ones. Especially in extreme cases for example high number of philosophers (>200) or short times to eat and/or sleep (<60 ms).
