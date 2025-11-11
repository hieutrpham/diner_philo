/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:13:39 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 16:17:04 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define MAX_THREAD 300
# define DEAD 1
# define ALIVE 2
# define DELAY 500
# define BEGIN 1
# define PANIC 2

typedef struct s_sim	t_sim;
typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					req_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	atomic_ullong		last_eat_time;
	size_t				num_philos;
	atomic_int			meal_eaten;
	atomic_int			*status;
	t_sim				*sim;
	pthread_mutex_t		*lf;
	pthread_mutex_t		*rf;
	pthread_mutex_t		*print_lock;
}						t_philo;

typedef struct s_sim
{
	pthread_mutex_t		print_lock;
	atomic_int			status;
	atomic_int			begin;
	t_philo				*philos;
}						t_sim;

bool					check_arg(int ac, char **av);
int						ft_atoi(const char *nptr);
size_t					ft_strlen(const char *s);
void					*monitor_routine(void *arg);
size_t					get_time(void);
void					print_mes(char *mes, t_philo *philo);
void					*philo_routine(void *arg);
void					init_sim(t_sim *sim, t_philo *philos);
void					init_philos(char **av, t_sim *sim,
							pthread_mutex_t *forks);
int						philo_create(t_sim *sim, char **av);
bool					philo_join(t_sim *sim, char **av);
bool					stop_sim(t_philo *philo);
bool					monitor_create(t_sim *sim, pthread_t *monitor);
#endif // PHILO_H
