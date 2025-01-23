/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:20:06 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/23 12:12:04 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(char **argv, t_data *data)
{
	int				i;
	t_philosophers	*philos;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (ERROR);
	data->number_of_philos = (int)ft_atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
	{
		free(data);
		return (ERROR);
	}
	philos = malloc(sizeof(t_philosophers) * data->number_of_philos);
	if (!philos)
	{
		free(data->forks);
		free(data);
		return (ERROR);
	}
	while (i < data->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		i++;
	}
	data->philos = philos;
	return (SUCCESS);
}

int	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
	{
		while (i < data->number_of_philos)
		{
			pthread_mutex_destroy(&(data->philos[i].meal_lock));
			i++;
		}
		free(data->philos);
	}
	i = 0;
	if (data->forks)
	{
		while (i < data->number_of_philos)
		{
			pthread_mutex_destroy(&(data->forks[i]));
			i++;
		}
		free(data->forks);
	}
	free(data);
	data = NULL;
	return (SUCCESS);
}

int	init(char **argv, t_data *data)
{
	if (init_data(argv, data))
		return (ERROR);
	return (SUCCESS);
}
