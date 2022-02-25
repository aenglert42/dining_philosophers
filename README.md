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
* [Resources](#resources)
* [Notes](#notes)

## Introduction
###### <p align="right">Next: [Approach](#approach)&emsp;&emsp;[[Contents](#table-of-contents)]</p>

### Allowed functions
memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

### Description
The aim of the exercise is to write a program which does a simulation of the dining philosophers. The situation is as follows:
One or more philosophers sit around a round table. Each philosopher has their own place at the table with a plate and a fork on its right-hand side.

The dish served is a very difficult kind of spaghetti, that has to be eaten with two forks. To achieve this the philosophers have to also use the fork of their neighbor. As a consequence philosophers sitting next to each other can not eat simultaneously.

The philosophers are alternatively eating, sleeping or thinking. When a philosopher has finished eating, they put the forks back on the table and start sleeping. Once awake, they start thinking. The simulation stops when a philosopher dies of starvation. This should be avoided. However philosophers don’t speak with each other and don’t know if another philosopher is about to die.

_Illustration[^1] of the "dining philosophers problem"_:
[^1]: From Wikipedia: https://en.wikipedia.org/wiki/Dining_philosophers_problem
<img src="https://user-images.githubusercontent.com/80413516/154969574-e0201e98-c453-4f77-9eba-93da381f5783.png" width="500">

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
###### <p align="right">Next: [Prerequisites](#prerequisites)&emsp;Previous: [Introduction](#introduction)&emsp;&emsp;[[Contents](#table-of-contents)]</p>

I started to learn and experiment with threads watching the videos linked in the [resources](#resources). I learned [how to create threads](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2), [how to pass arguments to threads](https://www.youtube.com/watch?v=HDohXvS6UIk&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=7) and [how to use mutex locks](https://www.youtube.com/watch?v=oq29KUy29iQ&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=4).

Basically every philosopher (thread) is going to executing an infinie while loop with the philosopher's routine (eat-sleep-think-repeat, as described above), until one of them dies of starvation or all of them have eaten the number of required meals. As they should not communicate with each other, a external control instance is needed.

The tricky part of this project comes with the parallelism and the use of shared resources (e.g. the forks). To prevent _[data races](https://www.youtube.com/watch?v=FY9livorrJI&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=3)_ the shared resources have to be protected using _mutex_locks_. This has to be coordinated in a way that no _[deadlocks](https://www.youtube.com/watch?v=LjWug2tvSBU&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=19)_ can occure.

I approached this project in three main steps. First I created the "[frame](#frame)" that sets up the simulation. After this I worked out the [routine](#routine) and ended with the external [control instance](#control-instance).

### Frame
For the frame my goal was to code the program up to the point were it would recieve the user input from the command line, do the input error checking and launch the right number of threads (given by the user input) that will run the routine. For now the routine should only print what I call the philosopher_id (the number of the philosopher from 1 to n). Once I managed that, I went on with the routine.

### Routine
I changed from printing the philosopher_id to printing the required logs, as stated above. To have an easyer start, I first developed the routine without using any mutex_locks, ignoring the fact that a fork can not be used by two philosophers at the same time. When I got this going, I protected the forks of simultaneous use by locking and unlocking the corresponding mutex_locks.

### Control Instance
I developed a control function that constantly loops through all the philosophers and checks if a one of them has to die or they ate all their meals. If I detect one of the mentioned cases, I set a flag (which is checked by the philosophers constantly) to indicate that the simulation has to end. I lock the log printing so that no further logs get printed after the notification of the death. ***The flag and all other shared variables have to be protected with mutex_locks***.

## Prerequisites
###### <p align="right">Next: [How to launch](#how-to-launch)&emsp;Previous: [Approach](#approach)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
* gcc (```sudo apt-get install gcc```)
* make (```sudo apt-get install make```)
* pthread (```$ sudo apt-get install libpthread-stubs0-dev```)


## How to launch
###### <p align="right">Next: [Example](#example)&emsp;Previous: [Prerequisites](#prerequisites)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
Compile the program via the Makefile by using ```$ make``` in the root directory of the repository.

Run it like this:

```
$ ./philo 4 800 200 200
```
For a description of the arguments see: [Arguments](#arguments).


## Example
###### <p align="right">Next: [Resources](#resources)&emsp;Previous: [How to launch](#how-to-launch)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
Terminal output for the following examples:

* __Example 1__ _"2 120 60 60 2"_: The program stops after both philosophers ate at least two times.
* __Example 2__ _"2 800 600 300"_: A philosopher dies because at 800 ms (when he should eat again to stay alive), he is still sleeping.
* __Example 3__ _"4 400 200 200"_: Nobody dies and no limit is set.

| __Example 1__ | __Example 2__ | __Example 3__ |
| :---- | :---- | :---- |
| ![Philosphers1](https://user-images.githubusercontent.com/80413516/155484192-e887fb65-a58b-445a-b8cb-93df346184a7.gif) | ![Philosphers2](https://user-images.githubusercontent.com/80413516/155485691-d0efe8bb-9e02-4f41-a716-44b1d0a2a6a5.gif) | ![Philosphers3](https://user-images.githubusercontent.com/80413516/155485700-f430e75f-c312-4b41-86bd-c2aa6fb8d71a.gif) |

## Resources
###### <p align="right">Next: [Notes](#notes)&emsp;Previous: [Example](#example)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
[Code Vault: Playlist - Unix Threads in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) Video 1 (Short introduction to threads) - Video 7 (How to pass arguments to threads in C)

[Jacob Sorber: Playlist - Programming with Threads](https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM) Video 1 (How to create and join threads in C) - Video 3 (Safety and Speed Issues with Threads)

## Notes
###### <p align="right">Previous: [Resources](#resources)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
Depending on the performance of the Computer philosphers may die (faster) on slower computers, but live on faster ones. Especially in extreme cases for example high number of philosophers (>200) or short times to eat and/or sleep (<60 ms).
