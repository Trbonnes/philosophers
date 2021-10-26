# 42 Cursus philosophers

Extract from the Project Subject :

" In this project, you will learn the basics of threading a process. You will
learn how to make threads. You will discover the mutex. "

---

Trbonnes philosophers
===============

### Overview
This project is written in C and is designed to run on MacOS.
You will find three different programs :
- philo_one using multi-threading and mutexes
- philo_two using multi-threading and semaphores
- philo_three using multi-processing and semaphores

The aim of this project is to practice multi-threading and multi-processing.
We have a group of philosophers around a table eating and thinking. Each philosopher have a fork but he needs two to eat, so he must take the fork of another philosopher.
The philosophers can't talk to each other, and if a philosopher doesn't eat for a certain amount of time, he will die.

### Tests
Each program have it's own makefile.
You can run a program with the following arguments:
- number_of_philosophers
- time_to_die
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_times_each_philosopher_must_eat (optional)

Now you juste have to wait and see if one of them dies from hunger.

### Contact
trbonnes@student.42.fr
