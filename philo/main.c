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
#include <pthread.h>
#include <string.h>

#ifndef THREAD_COUNT
#define THREAD_COUNT 10
#endif // THREAD_COUNT

#define SLEEP 500
#define DIE 500
#define EAT 500

int get_time()
{
	struct timeval tv;
	int t = gettimeofday(&tv, NULL);
	if (t < 0)
		return (printf("%s\n", strerror(errno)));
	return tv.tv_sec*1000 + tv.tv_usec/1000;
}

void print_mes(char *mes, t_philo *philo)
{
	pthread_mutex_lock(philo->print_mt);
	printf("philo %d %s\n", philo->id, mes);
	pthread_mutex_unlock(philo->print_mt);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lf);
	print_mes("has taken a fork", philo);
	pthread_mutex_lock(philo->rf);
	print_mes("has taken a fork", philo);
	print_mes("is eating", philo);
	usleep(EAT);
	pthread_mutex_unlock(philo->rf);
	pthread_mutex_unlock(philo->lf);
}

void think(t_philo *philo)
{
	print_mes("is thinking", philo);
}

void sleeps(t_philo *philo)
{
	print_mes("is sleeping", philo);
	usleep(SLEEP);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(500);
	eat(philo);
	sleeps(philo);
	think(philo);
	return NULL;
}

void *monitor_routine()
{
	return NULL;
}

int main(void)
{
	t_philo philos[THREAD_COUNT] = {0};
	pthread_mutex_t forks[THREAD_COUNT] = {0};
	pthread_mutex_t print_mt;
	pthread_t monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
		return printf("thread created error: %s\n", strerror(errno));

	pthread_mutex_init(&print_mt, NULL);
	// initialize the philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		philos[i].print_mt = &print_mt;
		philos[i].id = i + 1;
		if (philos[i].id == THREAD_COUNT)
			philos[i].lf = &forks[0];
		else
			philos[i].lf = &forks[philos[i].id];
		if (philos[i].id == 1)
			philos[i].rf = &forks[0];
		else
			philos[i].rf = &forks[philos[i].id - 1];
		// printf("philo %d lf: %p rf: %p\n", philos[i].id, philos[i].lf, philos[i].rf);
	}

	// create threads as philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
			return (printf("thread create error: %s\n", strerror(errno)));
	}
	
	//join all philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (printf("thread create error: %s\n", strerror(errno)));
	}

	return 0;
}
