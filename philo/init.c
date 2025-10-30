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

void	init_sim(t_sim *sim, t_philo *philos)
{
	sim->status = ALIVE;
	pthread_mutex_init(&(sim->print_lock), NULL);
	pthread_mutex_init(&(sim->dead_lock), NULL);
	pthread_mutex_init(&(sim->meal_lock), NULL);
	sim->philos = philos;
}

static void	init_philos_constants(char **av, t_sim *sim)
{
	size_t	start_time;
	int		i;

	i = 0;
	start_time = get_time();
	while (i < ft_atoi(av[1]))
	{
		sim->philos[i].start_time = start_time;
		sim->philos[i].last_eat_time = start_time;
		sim->philos[i].num_philos = ft_atoi(av[1]);
		sim->philos[i].time_to_die = ft_atoi(av[2]);
		sim->philos[i].time_to_eat = ft_atoi(av[3]);
		sim->philos[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			sim->philos[i].req_meal = ft_atoi(av[5]);
		sim->philos[i].print_lock = &(sim->print_lock);
		sim->philos[i].dead_lock = &(sim->dead_lock);
		sim->philos[i].meal_lock = &(sim->meal_lock);
		sim->philos[i].meal_eaten = 0;
		sim->philos[i].status = &(sim->status);
		sim->philos[i].id = i + 1;
		i++;
	}
}

void	init_philos(char **av, t_sim *sim, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	init_philos_constants(av, sim);
	while (i < ft_atoi(av[1]))
	{
		if (sim->philos[i].id == ft_atoi(av[1]))
			sim->philos[i].lf = &forks[0];
		else
			sim->philos[i].lf = &forks[sim->philos[i].id];
		if (sim->philos[i].id == 1)
			sim->philos[i].rf = &forks[0];
		else
			sim->philos[i].rf = &forks[sim->philos[i].id - 1];
		i++;
	}
}
