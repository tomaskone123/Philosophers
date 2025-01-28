/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:14 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/28 16:19:56 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_lifecycle(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->input->meals_required == 0)
		return (NULL);
	if (philo->input->start_time == 0)
		philo->input->start_time = get_time_in_ms();
	while (1)
	{
		think(philo);
		take_fork(philo);
		eat(philo);
		put_fork(philo);
		sleep(philo);
		if (philo->input->meals_required > 0
			&&philo->meals_eaten >= philo->input->meals_required)
	}
}
