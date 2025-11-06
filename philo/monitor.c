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
	size_t time;

	time = get_time();
	pthread_mutex_lock(philo->meal_lock);
	if (time - philo->last_eat_time > philo->time_to_die)
	{
		pthread_mutex_lock(philo->print_lock);
		printf("%zu %d died\n", time - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->print_lock);
		pthread_mutex_lock(philo->dead_lock);
		*philo->status = DEAD;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->meal_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

bool stop_sim(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->status == DEAD)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return true;
	}
	pthread_mutex_unlock(philo->dead_lock);
	return false;
}

static int	has_dead_philo(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0].num_philos)
	{
		if (is_dead(&philos[i]))
			return (philos[i].id);
		i++;
	}
	return (-1);
}

static bool	all_eaten(t_philo *philos)
{
	size_t	i;
	size_t	num_philos;

	i = 0;
	num_philos = 0;
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock(philos[0].meal_lock);
		if (philos[i].meal_eaten >= philos[i].req_meal)
			num_philos++;
		pthread_mutex_unlock(philos[0].meal_lock);
		i++;
	}
	if (num_philos == philos[0].num_philos)
		return (true);
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (true)
	{
		if (has_dead_philo(philos) >= 0)
			break ;
		if (philos[0].req_meal && all_eaten(philos))
		{
			pthread_mutex_lock(philos[0].dead_lock);
			*philos[0].status = DEAD;
			pthread_mutex_unlock(philos[0].dead_lock);
			break ;
		}
		usleep(1);
	}
	return (NULL);
}
