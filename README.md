# diner_philo

C implementation of the classic **Dining Philosophers** concurrency problem (42 school project), including:

- `philo/` — mandatory version using **threads + mutexes**
- `philo_bonus/` — bonus version using **processes + semaphores**

> Goal: model philosophers that alternate between eating, sleeping, and thinking while competing for shared forks, without deadlocks and while respecting timing constraints.

## Repository layout

- `philo/` — mandatory implementation
  - `Makefile`
  - `*.c`, `philo.h`
- `philo_bonus/` — bonus implementation
  - `Makefile`
  - `*.c`, `philo.h`

## Build

### Mandatory

```bash
cd philo
make
```

This produces the `philo` executable.

### Bonus

```bash
cd philo_bonus
make
```

This produces the `philo_bonus` executable.

## Usage

### Mandatory (`philo`)

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Bonus (`philo_bonus`)

```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

- `number_of_philosophers` — number of philosophers (and forks)
- `time_to_die` — time (ms) until a philosopher dies if they don’t eat
- `time_to_eat` — eating duration (ms)
- `time_to_sleep` — sleeping duration (ms)
- `number_of_times_each_philosopher_must_eat` *(optional)* — stop once everyone has eaten this many times

## Output

The program prints timestamped state transitions such as:

- `[timestamp][philo_id] has taken a fork`
- `[timestamp][philo_id] is eating`
- `[timestamp][philo_id] is sleeping`
- `[timestamp][philo_id] is thinking`
- `[timestamp][philo_id] died`

## Notes

- Mandatory version uses `pthread` threads and mutexes to protect forks and shared state.
- Bonus version uses multiple processes and POSIX semaphores.

## CI

A GitHub Actions workflow is included at `.github/workflows/c-cpp.yml`.
