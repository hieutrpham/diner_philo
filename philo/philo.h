/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:13:39 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 14:39:39 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_THREAD 300

typedef enum s_status
{
	DEAD = 1,
	ALIVE
}					t_status;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t			req_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			last_eat_time;
	size_t			num_philos;
	size_t			meal_eaten;
	_Atomic t_status *status;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_sim
{
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	_Atomic t_status status;
	t_philo			*philos;
}					t_sim;

bool				check_arg(int ac, char **av);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
void				*monitor_routine(void *arg);
size_t	get_time(void);
int	ft_usleep(size_t ms);
void	print_mes(char *mes, t_philo *philo);
void	*philo_routine(void *arg);
#endif // PHILO_H
