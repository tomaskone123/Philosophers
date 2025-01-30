/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:49:34 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/30 14:45:44 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		while (i < data->input->number_of_philos)
		{
			pthread_mutex_lock(&data->philos[i]->meal_lock);
			if (get_time_in_ms()
				- data->philos[i]->last_meal_time > data->input->time_to_die)
				pthread_mutex_unlock(&data->philos[i]->meal_lock);
				pthread_mutex_lock(&data->simulation_lock);
				data->is_running = 0;
				pthread_mutex_unlock(&data->simulation_lock);
				i++;
				pritnt_status(data->philos[i], "died"); // TO DO
			pthread_mutex_unlock(&data->philos[i]->meal_lock);
		}
		usleep(1000);
	}
	return (NULL);
}
