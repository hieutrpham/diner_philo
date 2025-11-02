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
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 300

typedef enum s_status
{
	DEAD = 1,
	ALIVE
}					t_status;

typedef struct s_philo
{
	int					id;
	size_t				req_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	size_t				last_eat_time;
	size_t				num_philos;
	size_t				meal_eaten;
	sem_t				*status;
	sem_t				*print_lock;
	sem_t				*dead_lock;
	sem_t				*meal_lock;
}						t_philo;

typedef struct s_sim
{
	sem_t		meal_lock;
	sem_t		print_lock;
	sem_t		dead_lock;
	sem_t		status;
	t_philo		*philos;
	pid_t		pids;
}					t_sim;

bool				check_arg(int ac, char **av);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
void				*monitor_routine(void *arg);
size_t				get_time(void);
int					ft_usleep(size_t ms);
void				print_mes(char *mes, t_philo *philo);
void				*philo_routine(void *arg);
void				init_sim(t_sim *sim, t_philo *philos, pid_t *pids);
void				init_philos(char **av, t_sim *sim);
bool				thread_create(t_sim *sim, char **av, pthread_t *monitor);
bool				thread_join(t_sim *sim, char **av, pthread_t monitor);
#endif // PHILO_H
