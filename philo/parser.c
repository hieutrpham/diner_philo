/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:35:33 by trupham           #+#    #+#             */
/*   Updated: 2025/10/28 17:35:22 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	usage(void)
{
	printf("Invalid Usage:\n");
	printf("    ./philo n t1 t2 t3 [m]\n");
	printf("        n : number of philo\n");
	printf("        t1: time to die\n");
	printf("        t2: time to eat\n");
	printf("        t3: time to sleep\n");
	printf("        m : number of meals to eat\n");
	return (false);
}

static bool	check_arg_len(const char *s)
{
	if (ft_strlen(s) > 9)
	{
		write(2, "Invalid argument number\n", 25);
		return (false);
	}
	return (true);
}

static bool	check_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (!check_arg_len(av[i]))
			return (false);
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				write(2, "Invalid arguments\n", 19);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_arg(int ac, char **av)
{
	if (ac < 2 || ac > 6 || ac < 5)
		return (usage());
	if (!check_digit(av))
		return (false);
	if (ft_atoi(av[1]) == 0)
	{
		write(2, "No philo no fork\n", 18);
		return (false);
	}
	return (true);
}
