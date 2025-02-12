/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:19 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/11 16:13:15 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philosophers *philo)
{
	if (!check_running(philo))
		return ;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->input->meals_required)
	{
		philo->is_full = 1;
		philo->data->full_philos++;
	}
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, "is eating");
	delay(philo->input->time_to_eat);
}

void	think(t_philosophers *philo)
{
	if (!check_running(philo))
		return ;
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
	if (!check_running(philo))
		return ;
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	philo->first_f = 1;
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	philo->second_f = 1;
	print_action(philo, "has taken a fork");
}

void	put_fork(t_philosophers *philo)
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
