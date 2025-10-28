/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:14:13 by trupham           #+#    #+#             */
/*   Updated: 2025/10/28 14:19:35 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


size_t get_time()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (write(2, "Error getting time\n", 20));
	return tv.tv_sec*1000 + tv.tv_usec/1000;
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
	return (0);
}

bool is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	size_t time = get_time();
	if(time - philo->start_time > philo->time_to_die
		|| time - philo->last_eat_time > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return true;
	}
	pthread_mutex_unlock(philo->dead_lock);
	return false;
}

void print_mes(char *mes, t_philo *philo)
{
	size_t time;

	pthread_mutex_lock(philo->print_lock);
	time = get_time() - philo->start_time;
	if (*philo->status != DEAD)
		printf("%zu %d %s\n", time, philo->id, mes);
	pthread_mutex_unlock(philo->print_lock);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lf);
	print_mes("has taken a fork", philo);
	pthread_mutex_lock(philo->rf);
	print_mes("has taken a fork", philo);
	print_mes("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_eat_time = get_time();
	philo->meal_eaten += 1;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
}

void think(t_philo *philo)
{
	print_mes("is thinking", philo);
}

void sleeps(t_philo *philo)
{
	print_mes("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (*philo->status != DEAD)
	{
		eat(philo);
		sleeps(philo);
		think(philo);
	}
	return NULL;
}

int has_dead_philo(t_philo *philos)
{
	size_t i = 0;

	while (i < philos[0].num_philos)
	{
		if (is_dead(&philos[i]))
			return i;
		i++;
	}
	return -1;
}

bool all_eaten(t_philo *philos)
{
	size_t i;
	size_t num_philos;

	i = 0;
	num_philos = 0;
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock((&philos[0])->meal_lock);
		if (philos[i].meal_eaten >= philos[i].req_meal)
			num_philos++;
		pthread_mutex_unlock((&philos[0])->meal_lock);
		i++;
	}
	if (num_philos == (&philos[0])->num_philos)
		return true;
	return false;
}

void *monitor_routine(void *arg)
{
	t_philo *philos = (t_philo *)arg;

	while (true)
	{
		int dead = has_dead_philo(philos);
		if (dead >= 0 || philos[0].num_philos <= 1)
		{
			pthread_mutex_lock((&philos[0])->print_lock);
			*(&philos[0])->status = DEAD;
			printf("%zu %d died\n", get_time() - (&philos[0])->start_time, dead + 1);
			pthread_mutex_unlock((&philos[0])->print_lock);
			break;
		}
		if (philos[0].req_meal && all_eaten(philos))
			break;
	}
	return NULL;
}

int main(int ac, char **av)
{
	if (!check_arg(ac, av))
		return 1;
	t_philo philos[MAX_THREAD] = {0};
	pthread_mutex_t forks[MAX_THREAD] = {0};
	pthread_mutex_t print_lock;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_lock;
	pthread_t monitor;
	_Atomic t_status status = ALIVE;

	pthread_mutex_init(&print_lock, NULL);
	pthread_mutex_init(&dead_lock, NULL);
	pthread_mutex_init(&meal_lock, NULL);
	size_t start_time = get_time();

	// initialize the philos
	for (int i = 0; i < ft_atoi(av[1]); i++)
	{
		philos[i].start_time = start_time;
		philos[i].num_philos = ft_atoi(av[1]);
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			philos[i].req_meal = ft_atoi(av[5]);
		philos[i].last_eat_time = start_time;
		philos[i].print_lock = &print_lock;
		philos[i].dead_lock = &dead_lock;
		philos[i].meal_lock = &meal_lock;
		philos[i].meal_eaten = 0;
		philos[i].status = &status;

		//rf = (id + 1) % philo_count
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
		return write(2, "thread created error: %s\n", 26);

	// create threads as philos
	for (int i = 0; i < ft_atoi(av[1]); i++)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
			return write(2, "thread created error: %s\n", 26);
	}
	
	//join all philos
	for (int i = 0; i < ft_atoi(av[1]); i++)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return write(2, "thread created error: %s\n", 26);
	}

	// cleanup
	pthread_join(monitor, NULL);
	pthread_mutex_destroy(&print_lock);
	pthread_mutex_destroy(&dead_lock);
	pthread_mutex_destroy(&meal_lock);
	return 0;
}
