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

static void	eat(t_philo *philo)
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
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
}

static void	think(t_philo *philo)
{
	print_mes("is thinking", philo);
}

static void	sleeps(t_philo *philo)
{
	print_mes("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	if (philo->num_philos == 1)
	{
		pthread_mutex_lock(philo->lf);
		print_mes("has taken a fork", philo);
		pthread_mutex_unlock(philo->lf);
		return (NULL);
	}
	while (*philo->status != DEAD)
	{
		eat(philo);
		sleeps(philo);
		think(philo);
	}
	return (NULL);
}
