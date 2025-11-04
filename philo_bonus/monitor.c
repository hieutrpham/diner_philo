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
	sem_wait(philo->dead_lock);
	if (get_time() - philo->last_eat_time > philo->time_to_die)
		return (true);
	sem_post(philo->dead_lock);
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
			ft_sem_close(philo, 0);
		}
	}
	return (NULL);
}
