/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:49:37 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/18 15:16:31 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*stopprocess(t_data *data, int i)
{
	if (data->full_philos == data->input->number_of_philos)
		print_action(data->philos[i], FINISH_EATING);
	else
		print_action(data->philos[i], DIED);
	pthread_mutex_unlock(&data->philos[i]->meal_lock);
	pthread_mutex_lock(&data->simulation_lock);
	data->is_running = 0;
	pthread_mutex_unlock(&data->data_lock);
	pthread_mutex_unlock(&data->simulation_lock);
	return (NULL);
}

int	check_running(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (!philo->data->is_running)
	{
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
	return (1);
}

void	philo_actions(t_philosophers *philo)
{
	take_fork(philo);
	eat(philo);
	put_fork(philo);
	sleeps(philo);
	think(philo);
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
		return (ERROR);
	}
	return (SUCCESS);
}
