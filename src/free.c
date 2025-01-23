/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:49:26 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/23 17:04:11 by tkonecny         ###   ########.fr       */
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
	free(data->forks);
	pthread_mutex_destroy(&data->print_lock);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	free_mutex(data);
	while (i < data->input->number_of_philos)
	{
		free(data->philos[i]);
		i++;
	}
	free(data->philos);
}
