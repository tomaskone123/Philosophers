/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:19 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/05 13:16:16 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (!philo->data->is_running)
		return ;
	pthread_mutex_unlock(&philo->data->simulation_lock);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, "is eating");
	usleep(philo->input->time_to_eat);
}
void	think(t_philosophers *philo)
{
	if (!philo->data->is_running)
		return ;
	print_action(philo, "is thinking");
	usleep(1000);
}

void	take_fork(t_philosophers *philo)
{
	// fix not good enough
}

void	put_fork(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->data->forks[0]);
	pthread_mutex_unlock(&philo->data->forks[1]);
}


void	sleeps(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (!philo->data->is_running)
	{
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
	print_action(philo, "is sleeping");
	usleep(philo->input->time_to_sleep);
}
