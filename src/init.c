/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:20:06 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/30 14:38:27 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_philos(t_data *data, int n_of_philos)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philosophers *) * n_of_philos);
	if (!data->philos)
		return (error(INCORRECT_MALLOC, NULL));
	while (i < n_of_philos)
	{
		data->philos[i] = malloc(sizeof(t_philosophers));
		if (!data->philos[i])
			return (error(INCORRECT_MALLOC, data));
		data->philos[i]->id = i;
		data->philos[i]->meals_eaten = 0;
		data->philos[i]->last_meal_time = 0;
		data->philos[i]->data = data;
		if (pthread_mutex_init(&data->philos[i]->meal_lock, NULL))
			return (error(INCORRECT_MUTEX, data));
		i++;
	}
	return (SUCCESS);
}

int	init_mutex(t_data *data, int n_of_philos)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (error(INCORRECT_MUTEX, NULL));
	data->forks = malloc(sizeof(pthread_mutex_t) * n_of_philos);
	if (!data->forks)
		return (error(INCORRECT_MALLOC, NULL));
	if (pthread_mutex_init(&data->simulation_lock, NULL))
		return (error(INCORRECT_MUTEX, NULL));
	while (i < n_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (error(INCORRECT_MUTEX, NULL));
		i++;
	}
	return (SUCCESS);
}

int	init_data(t_data *data, t_input *input)
{
	data->input = input;
	if (init_mutex(data, input->number_of_philos))
		return (ERROR);
	if (init_philos(data, input->number_of_philos))
		return (ERROR);
	return (SUCCESS);
}

int	init_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input->number_of_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL, &philo_lifecycle,
				data->philos[i]))
			return (error(INCORRECT_THREAD, data));
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor, data))
		return (error(INCORRECT_THREAD, data));
	return (SUCCESS);
}
