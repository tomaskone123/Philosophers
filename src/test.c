/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:35:18 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/24 14:44:04 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(void)
{
	unsigned long	start_time = get_time_in_ms();
	printf("start_time: \n%lu\n", start_time);
	
	usleep(200000);
	
	unsigned long	current_time = get_time_in_ms();
	printf("current_time: \n%lu\n", current_time);
	return (0);
}
