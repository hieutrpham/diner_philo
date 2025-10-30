/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:45:21 by trupham           #+#    #+#             */
/*   Updated: 2025/10/28 14:42:27 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (true);
	return (false);
}

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	atoi;

	atoi = 0;
	i = 0;
	sign = 1;
	if (!nptr)
		return (-1);
	while (isspace(nptr[i]))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign = -sign;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		atoi = atoi * 10 + (nptr[i] - '0');
		i++;
	}
	return (atoi * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}
