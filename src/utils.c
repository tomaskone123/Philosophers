/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:03:30 by tomas             #+#    #+#             */
/*   Updated: 2025/01/29 13:53:28 by tkonecny         ###   ########.fr       */
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
	if ((c >= '0' && c <= '9') || c == '-' || c == '+')
		return (1);
	return (0);
}

int	numbercheck(char *argv[], int argc)
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

int	inputload(char **argv, t_input *input, int argc)
{
	input->start_time = 0;
	input->number_of_philos = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->meals_required = ft_atoi(argv[5]);
	else
		input->meals_required = -1;
	if (input->number_of_philos < 1 || input->number_of_philos > 200
		|| input->time_to_die <= 0 || input->time_to_eat <= 0
		|| input->meals_required <= -2)
		{
			printf("Error\n The input arguments are invalid");
			return (0);
		}
		return (1);
}

unsigned long get_time_in_ms(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
