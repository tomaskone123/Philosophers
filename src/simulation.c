/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:14 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/05 18:16:00 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*only_one_philo(t_philosophers *philo)
{
	print_action(philo, "has taken a fork");
	usleep(philo->input->time_to_die * 1000);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
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
	if (philo->id % 2 == 0)
		usleep(philo->input->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->simulation_lock);
		if (!philo->data->is_running)
		{
			pthread_mutex_unlock(&philo->data->simulation_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->simulation_lock);
		think(philo);
		take_fork(philo);
		eat(philo);
		put_fork(philo);
		sleeps(philo);
		if (philo->input->meals_required > 0
			&& philo->meals_eaten >= philo->input->meals_required)
			return (NULL);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->input->number_of_philos)
		{
			pthread_mutex_lock(&data->philos[i]->meal_lock);
			if (data->philos[i]->last_meal_time > 0 && get_time_in_ms()
				- data->philos[i]->last_meal_time > data->input->time_to_die)
			{
				print_action(data->philos[i], "died");
				pthread_mutex_lock(&data->simulation_lock);
				data->is_running = 0;
				pthread_mutex_unlock(&data->simulation_lock);
				pthread_mutex_unlock(&data->philos[i]->meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i]->meal_lock);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

void	print_action(t_philosophers *philo, char *action)
{
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (!philo->data->is_running)
	{
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lu\t %d %s\n", get_time_in_ms() - philo->data->input->start_time,
		philo->id, action);
	printf("id:\t\t%d\nmeal_eaten:\t%d\n", philo->id, philo->meals_eaten);
	pthread_mutex_unlock(&philo->data->print_lock);
}
