# Philosophers

The **Philosophers** project is a classic concurrency exercise from the École 42 curriculum. It is based on the "Dining Philosophers Problem," a well-known synchronization problem involving philosophers who alternately think, eat, and need forks to eat. The goal is to implement a solution that avoids deadlocks and starvation using threads and mutexes.

## Table of Contents

- [Project Overview](#project-overview)
- [How to Compile](#how-to-compile)
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Arguments](#arguments)
- [Example](#example)
- [Project Structure](#project-structure)
- [Implementation Details](#implementation-details)

## Project Overview

- Each philosopher is a thread.
- Forks are represented by mutexes.
- Philosophers must pick up two forks (mutexes) to eat.
- The program must avoid deadlocks and starvation.
- The simulation ends when a philosopher dies or all have eaten a required number of times.

## Prerequisites

- **GCC** (or compatible compiler like Clang)
- **Unix-like OS** (Linux or macOS)
- **`pthread` library** (included by default in most Unix systems)

## How to Compile

```sh
make
```

This will produce an executable named `philo`.

## Usage

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

- `number_of_philosophers`: Number of philosophers and forks (integer > 1)
- `time_to_die`: Time (in ms) a philosopher can go without eating before dying
- `time_to_eat`: Time (in ms) a philosopher spends eating
- `time_to_sleep`: Time (in ms) a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional): If all philosophers eat this many times, the simulation ends

### Example

```sh
./philo 5 800 200 200
```

This runs the simulation with 5 philosophers, 800ms to die, 200ms to eat, and 200ms to sleep.

## Project Structure

- `philo.c` – Main program logic
- `philo.h` – Header file with structures and prototypes
- `utils.c` – Utility functions
- `parsing.c` – Parsing the input
- `get_time.c` – Sets and gets the time
- `actions_handler.c` – Handles actions (eating, sleeping and thinking)
- `Makefile` – Build instructions

## Implementation Details

- Each philosopher is a thread.
- Forks are protected by mutexes to prevent race conditions.
- The program uses precise timing to check for philosopher deaths.
- Output is synchronized to avoid garbled logs.
- The simulation stops if a philosopher dies or all have eaten the required number of times.
