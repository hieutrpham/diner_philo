/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:36:37 by trupham           #+#    #+#             */
/*   Updated: 2025/10/29 14:36:55 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (write(2, "Error getting time\n", 20));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_mes(char *mes, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_time() - philo->start_time;
	if (!stop_sim(philo))
		printf("%zu %d %s\n", time, philo->id, mes);
	pthread_mutex_unlock(philo->print_lock);
}
