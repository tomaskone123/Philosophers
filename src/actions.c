/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:19 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/30 15:03:07 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, "is eating");			//to do !!!!!!!!!
	better_sleeps(philo->input->time_to_eat);	//to do !!!!!!!!!
}
void	think(t_philosophers *philo)
{
	
}

void	take_fork(t_philosophers *philo)
{

}


void	put_fork(t_philosophers *philo)
{

}

void	sleeps(t_philosophers *philo)
{

}
