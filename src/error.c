/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomas <tomas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:48:08 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/05 21:21:53 by tomas            ###   ########.fr       */
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
	else if (msg == JOIN_ERROR)
		printf("Error\nJoin_Error");
	return (ERROR);
}
