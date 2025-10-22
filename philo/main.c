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

#define THREAD_COUNT 3

int get_time()
{
	struct timeval tv;
	int t = gettimeofday(&tv, NULL);
	if (t < 0)
		return (printf("%s\n", strerror(errno)));
	return tv.tv_sec*1000 + tv.tv_usec/1000;
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	printf("thread %d pick up left fork\n", philo->id);
	pthread_mutex_lock(philo->lf);
	printf("thread %d pick up right fork\n", philo->id);
	pthread_mutex_lock(philo->rf);
	printf("thread %d is eating\n", philo->id);
	usleep(500);
	printf("thread %d release both forks\n", philo->id);
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
	printf("thread %d is thinking\n", philo->id);
	usleep(500);
	printf("thread %d is sleeping\n", philo->id);
	usleep(500);
	return NULL;
}

//thread is philo
//mutex is fork
int main(void)
{
	t_philo philos[THREAD_COUNT];
	pthread_mutex_t forks[THREAD_COUNT];

	// initialize the philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		philos[i].id = i + 1;
		if (i == THREAD_COUNT - 1)
			philos[i].lf = &forks[0];
		else
			philos[i].lf = &forks[philos[i].id];
		if (i == 0)
		{
			philos[i].rf = &forks[i];
			philos[i].lf = &forks[philos[i].id];
		}
		else
			philos[i].rf = &forks[philos[i].id - 1];
		printf("philo %d lf: %p rf: %p\n", philos[i].id, philos[i].lf, philos[i].rf);
	}

	// create threads as philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
	}
	
	//join all philos
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		pthread_join(philos[i].thread, NULL);
	}

	return 0;
}
