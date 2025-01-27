/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:14 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/27 17:06:16 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_lifecycle(void *arg)
{
	t_philosophers	*philo;
	
	philo = (t_philosophers *)arg;
	if (philo->input->meals_required == 0)
		return (NULL);
	while (1)
	{
		think(philo);
		take_fork(philo);
		eat(philo);
		put_fork(philo);
		sleep(philo);
		if (philo->input->meals_required > 0 && philo->meals_eaten >	= philo->input->meals_required)
	}
}
