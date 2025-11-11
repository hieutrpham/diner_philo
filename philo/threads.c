/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:29:51 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 16:17:00 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	monitor_create(t_sim *sim, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_routine, sim->philos) != 0)
	{
		write(2, "ERROR: pthread_create\n", 23);
		return (false);
	}
	if (pthread_join(*monitor, NULL) != 0)
	{
		pthread_detach(*monitor);
		write(2, "ERROR: pthread_join\n", 21);
		return (false);
	}
	return (true);
}

int	philo_create(t_sim *sim, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_create(&sim->philos[i].thread, NULL, philo_routine,
				&sim->philos[i]) != 0)
		{
			while (i >= 0)
				pthread_detach(sim->philos[i--].thread);
			sim->begin = PANIC;
			write(2, "ERROR: pthread_create\n", 23);
			return (i);
		}
		i++;
	}
	sim->begin = BEGIN;
	return (i);
}

bool	philo_join(t_sim *sim, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
		{
			write(2, "ERROR: pthread_join\n", 21);
			return (false);
		}
		i++;
	}
	return (true);
}
