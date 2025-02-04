/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:14 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/04 15:58:51 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*only_one_philo(t_philosophers *philo)
{
	print_action(philo, "has taken a fork");
	usleep(philo->input->time_to_die);
	return (NULL);
}

void	*philo_lifecycle(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->input->start_time == 0)
		philo->input->start_time = get_time_in_ms();
	if (philo->input->meals_required == 0)
		return (NULL);
	if (philo->data->input->number_of_philos == 1)
		only_one_philo(philo);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1 && philo->data->is_running)
	{
		if (philo->data->is_running)
			think(philo);
		if (philo->data->is_running)
			take_fork(philo);
		if (philo->data->is_running)
			eat(philo);
		if (philo->data->is_running)
			put_fork(philo);
		if (philo->data->is_running)
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
	while (data->is_running)
	{
		i = 0;
		while (i < data->input->number_of_philos)
		{
			pthread_mutex_lock(&data->philos[i]->meal_lock);
			if (get_time_in_ms()
				- data->philos[i]->last_meal_time > data->input->time_to_die)
			{
				print_action(data->philos[i], "died");
				pthread_mutex_lock(&data->simulation_lock);
				data->is_running = 0;
				pthread_mutex_unlock(&data->simulation_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i]->meal_lock);
			i++;
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
