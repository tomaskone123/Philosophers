/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:14 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/11 16:24:11 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*only_one_philo(t_philosophers *philo)
{
	print_action(philo, "has taken a fork");
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
	if (philo->id % 2 == 0)
	{
		think(philo);
		delay(philo->input->time_to_eat / 2);
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

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->input->number_of_philos)
		{
			pthread_mutex_lock(&data->philos[i]->meal_lock);
			if (data->full_philos == data->input->number_of_philos)
				data->all_meals_eaten = 1;
			if (data->philos[i]->meals_eaten > 0 && get_time_in_ms()
				- data->philos[i]->last_meal_time > data->input->time_to_die)
				return (stopprocess(data, i));
			if (data->all_meals_eaten)
				return (stopprocess(data, i));
			pthread_mutex_unlock(&data->philos[i]->meal_lock);
			i++;
		}
		delay(1);
	}
	return (NULL);
}

void	print_action(t_philosophers *philo, char *action)
{
	if (!check_running(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	if (ft_strncmp(action, "has eaten enough", 16) == 0)
		printf("%lu\tALL MEALS EATEN\n", get_time_in_ms()
			- philo->data->input->start_time);
	else
		printf("%lu\t%d %s\n", get_time_in_ms()
			- philo->data->input->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	delay(int delayed_time)
{
	unsigned long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < (unsigned long)delayed_time)
		usleep(1);
}
