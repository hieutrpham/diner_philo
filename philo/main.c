/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:14:13 by trupham           #+#    #+#             */
/*   Updated: 2025/10/22 12:30:03 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#ifndef THREAD_COUNT
#define THREAD_COUNT 3
#endif // THREAD_COUNT

#define DIE 300
#define EAT 500
#define SLEEP 500

size_t get_time()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (write(2, "Error getting time\n", 20));
	return tv.tv_sec*1000 + tv.tv_usec/1000;
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
	return (0);
}

bool is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	size_t time = get_time();
	if (time - philo->start_time > DIE
		|| time - philo->last_eat_time > DIE)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return true;
	}
	pthread_mutex_unlock(philo->dead_lock);
	return false;
}

void print_mes(char *mes, t_philo *philo)
{
	size_t time;

	pthread_mutex_lock(philo->print_lock);
	time = get_time() - philo->start_time;
	if (*philo->status != DEAD)
		printf("%zu %d %s\n", time, philo->id, mes);
	pthread_mutex_unlock(philo->print_lock);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lf);
	print_mes("has taken a fork", philo);
	pthread_mutex_lock(philo->rf);
	print_mes("has taken a fork", philo);
	print_mes("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_eat_time = get_time();
	philo->meal_eaten += 1;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(EAT);
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
}

void think(t_philo *philo)
{
	print_mes("is thinking", philo);
}

void sleeps(t_philo *philo)
{
	print_mes("is sleeping", philo);
	ft_usleep(SLEEP);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (*philo->status != DEAD)
	{
		eat(philo);
		sleeps(philo);
		think(philo);
	}
	return NULL;
}

int has_dead_philo(t_philo *philos)
{
	int i = 0;

	while (i < THREAD_COUNT)
	{
		if (is_dead(&philos[i]))
			return i;
		i++;
	}
	return -1;
}

void *monitor_routine(void *arg)
{
	t_philo *philos = (t_philo *)arg;

	while (true)
	{
		int dead = has_dead_philo(philos);
		if (dead >= 0)
		{
			pthread_mutex_lock((&philos[0])->print_lock);
			*(&philos[0])->status = DEAD;
			printf("%zu %d died\n", get_time() - (&philos[0])->start_time, dead + 1);
			pthread_mutex_unlock((&philos[0])->print_lock);
			break;
		}
	}
	return NULL;
}

int main(void)
{
	t_philo philos[THREAD_COUNT] = {0};
	pthread_mutex_t forks[THREAD_COUNT] = {0};
	pthread_mutex_t print_lock;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_lock;
	pthread_t monitor;
	_Atomic t_status status = ALIVE;

	pthread_mutex_init(&print_lock, NULL);
	pthread_mutex_init(&dead_lock, NULL);
	pthread_mutex_init(&meal_lock, NULL);
	size_t start_time = get_time();

	// initialize the philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		philos[i].start_time = start_time;
		philos[i].last_eat_time = start_time;
		philos[i].print_lock = &print_lock;
		philos[i].dead_lock = &dead_lock;
		philos[i].meal_lock = &meal_lock;
		philos[i].meal_eaten = 0;
		philos[i].status = &status;

		//rf = (id + 1) % philo_count
		philos[i].id = i + 1;
		if (philos[i].id == THREAD_COUNT)
			philos[i].lf = &forks[0];
		else
			philos[i].lf = &forks[philos[i].id];
		if (philos[i].id == 1)
			philos[i].rf = &forks[0];
		else
			philos[i].rf = &forks[philos[i].id - 1];
	}

	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
		return write(2, "thread created error: %s\n", 26);

	// create threads as philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
			return write(2, "thread created error: %s\n", 26);
	}
	
	//join all philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return write(2, "thread created error: %s\n", 26);
	}

	// cleanup
	pthread_join(monitor, NULL);
	pthread_mutex_destroy(&print_lock);
	pthread_mutex_destroy(&dead_lock);
	pthread_mutex_destroy(&meal_lock);
	return 0;
}
