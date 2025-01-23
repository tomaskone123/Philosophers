/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:20:06 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/23 14:46:04 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_data *data, int n_of_philos)
{
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * n_of_philos);
	if (!data->forks)
		return (0);
}

int	init_data(char **argv, t_data *data, t_input *input)
{
	data->input = input;
	if (!init_mutex(data, input->number_of_philos))
		return (0);
	return (1);
}
