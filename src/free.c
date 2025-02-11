/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:49:26 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/11 16:52:30 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input->number_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i]->meal_lock);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->simulation_lock);
	pthread_mutex_destroy(&data->print_lock);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input->number_of_philos)
	{
		if (pthread_join(data->philos[i]->thread, NULL))
			return (error(JOIN_ERROR, data));
		i++;
	}
	if (pthread_join(data->monitor, NULL))
		return (error(JOIN_ERROR, data));
	return (0);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	free_mutex(data);
	// join_threads(data);
	while (i < data->input->number_of_philos)
	{
		free(data->philos[i]);
		i++;
	}
	free(data->philos);
	free(data->forks);
}
