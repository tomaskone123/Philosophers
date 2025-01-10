/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:29:34 by tomas             #+#    #+#             */
/*   Updated: 2025/01/10 18:34:05 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (!argcheck(argv))
		return (1);
	if (!init(argv, &data, argc))
		return (1);
	return (0);
}



// number of philosophers
// time to day
// time to eat
// time to sleap
// *Number of how many times each philosopher needs to eat
