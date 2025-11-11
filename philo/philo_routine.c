/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:38:42 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 14:39:31 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	meal(t_philo *philo)
{
	unsigned long long	start;

	start = get_time();
	philo->last_eat_time = start;
	philo->meal_eaten += 1;
	print_mes("is eating", philo);
	while (get_time() - start < philo->time_to_eat)
	{
		if (stop_sim(philo))
			return ;
		usleep(DELAY);
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;

	if ((uintptr_t)philo->lf < (uintptr_t)philo->rf)
	{
		f1 = philo->lf;
		f2 = philo->rf;
	}
	else
	{
		f1 = philo->rf;
		f2 = philo->lf;
	}
	pthread_mutex_lock(f1);
	print_mes("has taken a fork", philo);
	pthread_mutex_lock(f2);
	print_mes("has taken a fork", philo);
	meal(philo);
	pthread_mutex_unlock(f2);
	pthread_mutex_unlock(f1);
}

static void	think(t_philo *philo)
{
	int	delay;

	print_mes("is thinking", philo);
	if (stop_sim(philo))
		return ;
	delay = (philo->time_to_die - philo->time_to_sleep - philo->time_to_eat)
		/ 2;
	if (delay > 0)
		usleep(delay * 1000);
}

static void	sleeps(t_philo *philo)
{
	size_t	start;

	print_mes("is sleeping", philo);
	start = get_time();
	while (get_time() - start < philo->time_to_sleep)
	{
		if (stop_sim(philo))
			return ;
		usleep(DELAY);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->sim->begin != BEGIN)
	{
		usleep(100);
		if (philo->sim->begin == PANIC)
			return (NULL);
	}
	print_mes("is thinking", philo);
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat * 1000 / 2);
	if (philo->num_philos == 1)
	{
		print_mes("has taken a fork", philo);
		return (NULL);
	}
	while (!stop_sim(philo))
	{
		eat(philo);
		sleeps(philo);
		think(philo);
	}
	return (NULL);
}
