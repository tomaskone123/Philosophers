/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomas <tomas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:19 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/05 21:24:14 by tomas            ###   ########.fr       */
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
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
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
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
}

void	sleeps(t_philosophers *philo)
{
	if (!check_running(philo))
		return ;
	print_action(philo, "is sleeping");
	delay(philo->input->time_to_sleep);
}
