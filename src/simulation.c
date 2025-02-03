/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:14 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/03 12:36:58 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_lifecycle(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->input->meals_required == 0)
		return (NULL);
	if (philo->input->start_time == 0)
		philo->input->start_time = get_time_in_ms();
	while (1)
	{
		think(philo);
		take_fork(philo);
		eat(philo);
		put_fork(philo);
		sleeps(philo);
		if (philo->input->meals_required > 0
			&& philo->meals_eaten >= philo->input->meals_required)
			return (NULL);
	}
}

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

void	print_action(t_philosophers *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lu %d %s\n", get_time_in_ms() - philo->data->input->start_time,
		philo->id, action);
	pthread_mutex_unlock(&philo->data->print_lock);
}
