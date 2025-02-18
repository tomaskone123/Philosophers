/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:14 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/18 15:17:14 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*only_one_philo(t_philosophers *philo)
{
	print_action(philo, FORK);
	delay(philo->input->time_to_die);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	return (NULL);
}

void	*philo_lifecycle(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->input->meals_required == 0)
		return (NULL);
	if (philo->data->input->number_of_philos == 1)
		return (only_one_philo(philo));
	if (philo->id % 2 != 1)
	{
		think(philo);
		delay(philo->input->time_to_eat);
	}
	while (1)
	{
		if (!check_running(philo))
			return (NULL);
		philo_actions(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	if (data->input->meals_required == 0)
		return (NULL);
	while (1)
	{
		i = 0;
		while (i < data->input->number_of_philos)
		{
			pthread_mutex_lock(&data->philos[i]->meal_lock);
			pthread_mutex_lock(&data->data_lock);
			if (data->philos[i]->meals_eaten > 0 && get_time_in_ms()
				- data->philos[i]->last_meal_time > data->input->time_to_die)
				return (stopprocess(data, i));
			if (data->full_philos == data->input->number_of_philos)
				return (stopprocess(data, i));
			pthread_mutex_unlock(&data->data_lock);
			pthread_mutex_unlock(&data->philos[i]->meal_lock);
			i++;
		}
		delay(1);
	}
	return (NULL);
}
