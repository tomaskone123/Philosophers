/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:48:08 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/30 14:47:44 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error(int msg, t_data *data)
{
	if (data)
		free_all(data);
	if (msg == INCORRECT_MALLOC)
		printf("Error\nMalloc failed\n");
	else if (msg == INCORRECT_MUTEX)
		printf("Error\nMutex failed\n");
	else if (msg == INCORRECT_THREAD)
		printf("Error\nThread failed\n");
	return (ERROR);
}
