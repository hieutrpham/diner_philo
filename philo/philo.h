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

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

typedef enum s_status
{
	DEAD = 1,
	ALIVE
} t_status;

typedef struct s_philo
{
	int id;
	pthread_t thread;
	size_t start_time;
	size_t last_eat_time;
	size_t meal_eaten;
	_Atomic t_status *status;
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
	_Atomic t_status status;
	t_philo *philos;
} t_sim;

#endif // PHILO_H
