/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:29:34 by tomas             #+#    #+#             */
/*   Updated: 2025/01/24 15:03:26 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_thread(t_data *data)
{
	int	i;
	
	i = 0;
	data->input->start_time = get_time_in_ms();
	while (i < data->input->number_of_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL, &philo_lifecycle, data->philos[i]))
			return (error(INCORRECT_THREAD, data));
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_input	input;

	if (!numbercheck(argv, argc) || !inputload(argv, &input, argc))
		return (EXIT_FAILURE);
	if (init_data(&data, &input))
		return (EXIT_FAILURE);
	if (init_thread(&data))
		return (EXIT_FAILURE);
	free_all(&data);
	return (EXIT_SUCCESS);
}

// number of philosophers
// time to die
// time to eat
// time to sleap
// *Number of how many times each philosopher needs to eat
