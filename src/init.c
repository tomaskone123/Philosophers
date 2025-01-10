/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:20:06 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/10 18:40:22 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
t_philo *init_philo(t_data *data, int argc)
{
	data = malloc(sizeof (t_data ));


}

int	init_data(char **argv, t_data *data, int argc)
{
	data = malloc(sizeof (t_data ));


}

int	init(char **argv, t_data *data, int argc)
{
	if (!init_data(argv, &data, argc))
		return (0);

}
