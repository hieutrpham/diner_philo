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
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_eat_time > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

static int	has_dead_philo(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0].num_philos)
	{
		if (is_dead(&philos[i]))
			return (i);
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
		pthread_mutex_lock((&philos[0])->meal_lock);
		if (philos[i].meal_eaten >= philos[i].req_meal)
			num_philos++;
		pthread_mutex_unlock((&philos[0])->meal_lock);
		i++;
	}
	if (num_philos == (&philos[0])->num_philos)
		return (true);
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		dead;

	philos = (t_philo *)arg;
	while (true)
	{
		dead = has_dead_philo(philos);
		if (dead >= 0)
		{
			pthread_mutex_lock((&philos[0])->print_lock);
			*(&philos[0])->status = DEAD;
			printf("%zu %d died\n", get_time() - (&philos[0])->start_time, dead
				+ 1);
			pthread_mutex_unlock((&philos[0])->print_lock);
			break ;
		}
		if (philos[0].req_meal && all_eaten(philos))
		{
			pthread_mutex_lock((&philos[0])->dead_lock);
			*(&philos[0])->status = DEAD;
			pthread_mutex_unlock((&philos[0])->dead_lock);
			break ;
		}
	}
	return (NULL);
}
