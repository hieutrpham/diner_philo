/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:13:39 by trupham           #+#    #+#             */
/*   Updated: 2025/10/22 11:24:52 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_philo
{
	int id;
	pthread_t thread;
	size_t start_time;
	size_t last_eat_time;
	size_t meal_eaten;
	_Atomic bool *dead;
	pthread_mutex_t *lf;
	pthread_mutex_t *rf;
	pthread_mutex_t *print_lock;
	pthread_mutex_t *dead_lock;
	pthread_mutex_t *meal_lock;
} t_philo;

typedef struct s_sim
{
	pthread_mutex_t meal_lock;
	pthread_mutex_t print_lock;
	pthread_mutex_t dead_lock;
	t_philo *philos;
} t_sim;
