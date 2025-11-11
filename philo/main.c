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

static int	mutex_destroy(t_sim *sim)
{
	pthread_mutex_destroy(&(sim->print_lock));
	return (1);
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
	if (philo_create(&sim, av) < ft_atoi(av[1]))
		return (mutex_destroy(&sim));
	monitor_create(&sim, &monitor);
	philo_join(&sim, av);
	mutex_destroy(&sim);
	return (0);
}
