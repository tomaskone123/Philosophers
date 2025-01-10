/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:03:30 by tomas             #+#    #+#             */
/*   Updated: 2025/01/10 18:13:01 by tkonecny         ###   ########.fr       */
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

int	argcheck(char* argv[])
{

	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
