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
	size_t	time;

	time = get_time();
	if (time - philo->last_eat_time > philo->time_to_die)
	{
		*philo->status = DEAD;
		pthread_mutex_lock(philo->print_lock);
		printf("%zu %d died\n", time - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->print_lock);
		return (true);
	}
	return (false);
}

bool	stop_sim(t_philo *philo)
{
	if (*philo->status == DEAD)
		return (true);
	return (false);
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
		if (philos[i].meal_eaten >= philos[i].req_meal)
			num_philos++;
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
	while (philos->sim->begin != BEGIN)
	{
		usleep(100);
		if (philos->sim->begin == PANIC)
			return (NULL);
	}
	while (true)
	{
		if (has_dead_philo(philos) >= 0)
			break ;
		if (philos[0].req_meal && all_eaten(philos))
		{
			*philos[0].status = DEAD;
			break ;
		}
		usleep(1);
	}
	return (NULL);
}
