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

typedef struct s_philo
{
	uint id;
	pthread_t thread;
	pthread_mutex_t *lf;
	pthread_mutex_t *rf;
	pthread_mutex_t *print_mt;
} t_philo;

typedef struct s_sim
{
	pthread_mutex_t print_lock;
	pthread_mutex_t dead_lock;
	t_philo *philos;
} t_sim;
