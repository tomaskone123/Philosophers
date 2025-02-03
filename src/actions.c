/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:19 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/03 15:21:57 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, "is eating");
	usleep(philo->input->time_to_eat);
}
void	think(t_philosophers *philo)
{
	print_action(philo, "is thinking");
	usleep(philo->input->time_to_sleep);
}

void	take_fork(t_philosophers *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[0]);
		pthread_mutex_lock(&philo->data->forks[1]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[1]);
		pthread_mutex_lock(&philo->data->forks[0]);
	}
}

void	put_fork(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->data->forks[0]);
	pthread_mutex_unlock(&philo->data->forks[1]);
}
