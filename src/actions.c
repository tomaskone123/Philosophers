/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:19 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/17 20:42:08 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	think(t_philosophers *philo)
{
	if (!check_running(philo))
		return ;
	print_action(philo, "is thinking");
	delay(1);
}

void	take_fork(t_philosophers *philo)
{
	int	first_fork;
	int	second_fork;

	if (!check_running(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		first_fork = (philo->id) % philo->input->number_of_philos;
		second_fork = philo->id - 1;
		pthread_mutex_lock(&philo->data->forks[first_fork]);
		philo->first_f = 1;
		pthread_mutex_lock(&philo->data->forks[second_fork]);
		philo->second_f = 1;
	}
	else
	{
		first_fork = philo->id - 1;
		second_fork = (philo->id) % philo->input->number_of_philos;
		pthread_mutex_lock(&philo->data->forks[first_fork]);
		philo->first_f = 1;
		pthread_mutex_lock(&philo->data->forks[second_fork]);
		philo->second_f = 1;
	}
	print_action(philo, "has taken a fork");
	print_action(philo, "has taken a fork");
}

void	put_fork(t_philosophers *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = (philo->id) % philo->input->number_of_philos;
		second_fork = philo->id - 1;
	}
	else
	{
		first_fork = philo->id - 1;
		second_fork = (philo->id) % philo->input->number_of_philos;
	}
	if (philo->first_f == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		philo->first_f = 0;
	}
	if (philo->second_f == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
		philo->second_f = 0;
	}
}

void	sleeps(t_philosophers *philo)
{
	if (!check_running(philo))
		return ;
	print_action(philo, "is sleeping");
	delay(philo->input->time_to_sleep);
}

void	eat(t_philosophers *philo)
{
	if (!check_running(philo))
		return ;
	pthread_mutex_lock(&philo->meal_lock);
	print_action(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->input->meals_required)
	{
		philo->is_full = 1;
		pthread_mutex_lock(&philo->data->data_lock);
		philo->data->full_philos++;
		pthread_mutex_unlock(&philo->data->data_lock);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	delay(philo->input->time_to_eat);
}
