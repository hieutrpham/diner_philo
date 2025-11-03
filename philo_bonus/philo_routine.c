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
	sem_wait(philo->forks);
	print_mes("has taken a fork", philo);
	sem_wait(philo->forks);
	print_mes("has taken a fork", philo);
	print_mes("is eating", philo);
	sem_wait(philo->meal_lock);
	philo->last_eat_time = get_time();
	philo->meal_eaten += 1;
	sem_post(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
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
	pthread_t monitor;

	philo = (t_philo *)arg;
	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
		return (printf("error pthread_create\n"), NULL);
	if (philo->num_philos == 1)
	{
		print_mes("has taken a fork", philo);
		return (NULL);
	}
	while (true)
	{
		eat(philo);
		sleeps(philo);
		think(philo);
	}
	return (NULL);
}
