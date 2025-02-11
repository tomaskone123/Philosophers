/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:29:34 by tomas             #+#    #+#             */
/*   Updated: 2025/02/11 13:33:47 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_input	input;

	if (numbercheck(argv, argc) || inputload(argv, &input, argc))
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
