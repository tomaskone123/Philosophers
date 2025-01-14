/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:20:06 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/14 19:12:55 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(char **argv, t_data *data, int argc)
{
	int	i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return(0);
	data->number_of_philos = (int) ft_atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
	{
		free(data);
		return (0);
	}
	t_philosophers *philos = malloc(sizeof(t_philosophers) * data->number_of_philos);
	if (!philos)
	{
		free(data->forks);
		free(data);
		return (0);
	}
	while (i < data->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten =0;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		i++;
	}
	return (1);
}


int	init(char **argv, t_data *data, int argc)
{
	if (!init_data(argv, &data, argc))
		return (0);

}
