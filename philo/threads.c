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

bool	thread_create(t_sim *sim, char **av, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_create(&sim->philos[i].thread, NULL, philo_routine,
				&sim->philos[i]) != 0)
		{
			write(2, "thread created error: %s\n", 26);
			return (false);
		}
		i++;
	}
	sim->begin = true;
	usleep(1000);
	if (pthread_create(monitor, NULL, monitor_routine, sim->philos) != 0)
	{
		write(2, "thread created error: %s\n", 26);
		return (false);
	}
	return (true);
}

bool	thread_join(t_sim *sim, char **av, pthread_t monitor)
{
	int	i;

	i = 0;
	if (pthread_join(monitor, NULL) != 0)
	{
		write(2, "thread joined error: %s\n", 25);
		return (false);
	}
	while (i < ft_atoi(av[1]))
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
		{
			write(2, "thread joined error: %s\n", 25);
			return (false);
		}
		i++;
	}
	return (true);
}
