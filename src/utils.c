/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:03:30 by tomas             #+#    #+#             */
/*   Updated: 2025/01/22 17:07:45 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	n;

	sign = 1;
	n = 0;
	while (((*nptr >= 9 && *nptr <= 13) || *nptr == ' ') && *nptr)
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while ((*nptr >= '0') && (*nptr <= '9'))
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}

static int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	argcheck(char *argv[], int argc)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error\n./philo [n-philos] [t-die] [t-eat] [t-sleep] *[n-eat]");
		return (0);
	}
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error\nOne of the inputs wasn't a number");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
