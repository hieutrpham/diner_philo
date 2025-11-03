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

int	main(int ac, char **av)
{
	static t_philo	philos[MAX_PHILO];
	static pid_t	pids[MAX_PHILO];
	t_sim			sim;

	sim = (t_sim){};
	if (!check_arg(ac, av))
		return (1);
	init_sim(&sim, philos, pids, av);
	init_philos(av, &sim);
	size_t i = 0;
	while (i < philos[0].num_philos)
	{
		pid_t id = fork();
		sim.pids[i] = id;
		if (id == 0)
			philo_routine(&philos[i]);
		i++;
	}
	waitpid(-1, NULL, 0);
	return (0);
}
