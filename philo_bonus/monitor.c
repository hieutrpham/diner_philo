/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:32:48 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 14:34:52 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_philo *philo)
{
	sem_wait(philo->meal_lock);
	if (get_time() - philo->last_eat_time > philo->time_to_die)
	{
		sem_post(philo->meal_lock);
		return (true);
	}
	sem_post(philo->meal_lock);
	return (false);
}

static bool	all_eaten(t_philo *philo)
{
	size_t	i;
	size_t	num_philos;

	i = 0;
	num_philos = 0;
	while (i < philo->num_philos)
	{
		sem_wait(philo->meal_lock);
		if (philo[i].meal_eaten >= philo[i].req_meal)
			num_philos++;
		sem_post(philo->meal_lock);
		i++;
	}
	if (num_philos == philo->num_philos)
		return (true);
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (is_dead(philo))
		{
			sem_wait(philo->print_lock);
			printf("%zu %d died\n", get_time() - philo->start_time, philo->id);
			sem_post(philo->dead_lock);
			exit(0);
		}
		if (philo->req_meal && all_eaten(philo))
		{
			sem_wait(philo->dead_lock);
			*philo->status = DEAD;
			sem_post(philo->dead_lock);
			exit(0);
		}
	}
	return (NULL);
}
