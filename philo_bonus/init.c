/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:45:13 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 16:23:18 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_sim(t_sim *sim, t_philo *philos, pid_t *pids, char **av)
{
	sem_unlink(PRINT_SEM);
	sem_unlink(DEAD_SEM);
	sem_unlink(MEAL_SEM);
	sem_unlink(FORK_SEM);
	sim->print_lock = sem_open(PRINT_SEM, O_CREAT | O_EXCL, 0644, 1);
	sim->dead_lock = sem_open(DEAD_SEM, O_CREAT | O_EXCL, 0644, 1);
	sim->meal_lock = sem_open(MEAL_SEM, O_CREAT | O_EXCL, 0644, 0);
	sim->forks = sem_open(FORK_SEM, O_CREAT | O_EXCL, 0644, ft_atoi(av[1]));
	sim->philos = philos;
	sim->pids = pids;
}

void	init_philos(char **av, t_sim *sim)
{
	size_t	start_time;
	int		i;

	i = 0;
	start_time = get_time();
	while (i < ft_atoi(av[1]))
	{
		sim->philos[i].pids = sim->pids;
		sim->philos[i].start_time = start_time;
		sim->philos[i].last_eat_time = start_time;
		sim->philos[i].num_philos = ft_atoi(av[1]);
		sim->philos[i].time_to_die = ft_atoi(av[2]);
		sim->philos[i].time_to_eat = ft_atoi(av[3]);
		sim->philos[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			sim->philos[i].req_meal = ft_atoi(av[5]);
		sim->philos[i].print_lock = sim->print_lock;
		sim->philos[i].dead_lock = sim->dead_lock;
		sim->philos[i].meal_lock = sim->meal_lock;
		sim->philos[i].meal_eaten = 0;
		sim->philos[i].forks = sim->forks;
		sim->philos[i].id = i + 1;
		i++;
	}
}
