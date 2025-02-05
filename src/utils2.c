/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:49:37 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/05 19:06:58 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i] || i == n - 1)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*stopprocess(t_data *data, int i)
{
	if (data->philos[i]->meals_eaten < data->input->meals_required)
		print_action(data->philos[i], "died");
	else
		print_action(data->philos[i], "has eaten enough");
	pthread_mutex_lock(&data->simulation_lock);
	data->is_running = 0;
	pthread_mutex_unlock(&data->simulation_lock);
	pthread_mutex_unlock(&data->philos[i]->meal_lock);
	return (NULL);
}

