/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:19 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/05 17:49:49 by tkonecny         ###   ########.fr       */
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
	usleep(philo->input->time_to_eat * 1000);
	print_action(philo, "is eating");
}
void	think(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (!philo->data->is_running)
	{
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
	print_action(philo, "is thinking");
}

void	take_fork(t_philosophers *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->id - 1;
		second_fork = (philo->id) % philo->input->number_of_philos;
	}
	else
	{
		second_fork = philo->id - 1;
		first_fork = (philo->id) % philo->input->number_of_philos;
	}
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (!philo->data->is_running)
	{
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_action(philo, "has taken a fork");

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
	usleep(philo->input->time_to_sleep * 1000);
	print_action(philo, "is sleeping");
}
