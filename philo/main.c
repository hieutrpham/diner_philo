/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:14:13 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 16:17:09 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_destroy(t_sim *sim)
{
	pthread_mutex_destroy(&(sim->print_lock));
}

int	main(int ac, char **av)
{
	static t_philo			philos[MAX_THREAD];
	static pthread_mutex_t	forks[MAX_THREAD];
	pthread_t				monitor;
	t_sim					sim;

	monitor = 0;
	if (!check_arg(ac, av))
		return (1);
	init_sim(&sim, philos);
	init_philos(av, &sim, forks);
	if (!thread_create(&sim, av, &monitor))
	{
		thread_join(&sim, av, monitor);
		mutex_destroy(&sim);
		return (1);
	}
	thread_join(&sim, av, monitor);
	mutex_destroy(&sim);
	return (0);
}
