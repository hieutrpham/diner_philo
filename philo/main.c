/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:14:13 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 14:38:57 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo			philos[MAX_THREAD] = {0};
	pthread_mutex_t	forks[MAX_THREAD] = {0};
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_t		monitor;
	size_t			start_time;

	if (!check_arg(ac, av))
		return (1);
	_Atomic t_status status = ALIVE;
	pthread_mutex_init(&print_lock, NULL);
	pthread_mutex_init(&dead_lock, NULL);
	pthread_mutex_init(&meal_lock, NULL);
	start_time = get_time();
	// initialize the philos
	for (int i = 0; i < ft_atoi(av[1]); i++)
	{
		philos[i].start_time = start_time;
		philos[i].last_eat_time = start_time;
		philos[i].num_philos = ft_atoi(av[1]);
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			philos[i].req_meal = ft_atoi(av[5]);
		philos[i].print_lock = &print_lock;
		philos[i].dead_lock = &dead_lock;
		philos[i].meal_lock = &meal_lock;
		philos[i].meal_eaten = 0;
		philos[i].status = &status;
		// rf = (id + 1) % philo_count
		philos[i].id = i + 1;
		if (philos[i].id == ft_atoi(av[1]))
			philos[i].lf = &forks[0];
		else
			philos[i].lf = &forks[philos[i].id];
		if (philos[i].id == 1)
			philos[i].rf = &forks[0];
		else
			philos[i].rf = &forks[philos[i].id - 1];
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
		return (write(2, "thread created error: %s\n", 26));

	// create threads as philos
	for (int i = 0; i < ft_atoi(av[1]); i++)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			return (write(2, "thread created error: %s\n", 26));
	}
	// join all philos
	for (int i = 0; i < ft_atoi(av[1]); i++)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (write(2, "thread created error: %s\n", 26));
	}
	// cleanup
	pthread_join(monitor, NULL);
	pthread_mutex_destroy(&print_lock);
	pthread_mutex_destroy(&dead_lock);
	pthread_mutex_destroy(&meal_lock);
	return (0);
}
