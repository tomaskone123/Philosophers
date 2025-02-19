/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:46:46 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/18 16:57:51 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	*get_status(t_status status)
{
	if (status == EAT)
		return ("is eating");
	else if (status == SLEEP)
		return ("is sleeping");
	else if (status == THINK)
		return ("is thinking");
	else if (status == FORK)
		return ("has picked up a fork");
	else if (status == DIED)
		return ("died");
	else
		return ("ALL MEALS EATEN");
}

char	*print_format(t_status status)
{
	if (status == EAT)
		return ("\033[7m%lu\033[0m\t\033[1;37m%d\033[0m \033[1;32m%s\033[0m\n");
	else if (status == SLEEP)
		return ("\033[7m%lu\033[0m\t\033[1;37m%d\033[0m \033[1;33m%s\033[0m\n");
	else if (status == THINK)
		return ("\033[7m%lu\033[0m\t\033[1;37m%d\033[0m \033[1;34m%s\033[0m\n");
	else if (status == FORK)
		return ("\033[7m%lu\033[0m\t\033[1;37m%d\033[0m \033[1;37m%s\033[0m\n");
	else if (status == DIED)
		return ("\033[7m%lu\033[0m\t\033[1;37m%d\033[0m \033[1;31m%s\033[0m\n");
	else
		return ("\033[7m%lu\033[0m\t\033[30m%d\033[0m \033[1;36m%s\033[0m\n");
}

void	print_action(t_philosophers *philo, t_status status)
{
	if (!check_running(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	printf(print_format(status), get_time_in_ms()
		- philo->data->input->start_time, philo->id, get_status(status));
	pthread_mutex_unlock(&philo->data->print_lock);
}
