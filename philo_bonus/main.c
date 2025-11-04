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
#include <bits/pthreadtypes.h>

void ft_sem_close(t_philo *philo, int sig)
{
	sem_close(philo->dead_lock);
	sem_close(philo->print_lock);
	sem_close(philo->meal_lock);
	sem_close(philo->forks);
	if (sig >= 0)
		exit(sig);
}

void	cleanup(t_philo *philo)
{
	size_t	i;

	i = 0;
	ft_sem_close(philo, -1);
	while (i < philo->num_philos)
		if (philo->pids[i] != -1)
			kill(philo->pids[i++], SIGKILL);
}

void	*meal_routine(void *arg)
{
	size_t	finish_eating;
	t_philo	*philos;

	philos = (t_philo *)arg;
	finish_eating = 0;
	while (true)
	{
		sem_wait(philos[0].meal_lock);
		finish_eating++;
		if (finish_eating >= philos[0].num_philos)
		{
			cleanup(&philos[0]);
			exit(0);
		}
	}
	return (NULL);
}

void	start_sim(t_sim *sim, t_philo *philos)
{
	size_t	i;
	pid_t	id;

	i = 0;
	while (i < philos[0].num_philos)
	{
		id = fork();
		sim->pids[i] = id;
		if (id == 0)
			philo_routine(&philos[i]);
		i++;
	}
	waitpid(-1, NULL, 0);
}

int	main(int ac, char **av)
{
	static t_philo	philos[MAX_PHILO];
	static pid_t	pids[MAX_PHILO];
	t_sim			sim;
	pthread_t		meal;

	sim = (t_sim){};
	if (!check_arg(ac, av))
		return (1);
	init_sim(&sim, philos, pids, av);
	init_philos(av, &sim);
	if (philos[0].req_meal > 0)
	{
		if (pthread_create(&meal, NULL, meal_routine, philos) != 0)
			ft_sem_close(&philos[0], 1);
		if (pthread_detach(meal) != 0)
			ft_sem_close(&philos[0], 1);
	}
	start_sim(&sim, philos);
	cleanup(&philos[0]);
	return (0);
}
