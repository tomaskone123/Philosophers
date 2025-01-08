/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomas <tomas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:22:11 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/09 00:08:11 by tomas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include <aio.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int		n;
	size_t	t_to_die;
	size_t	t_to_eat;
	size_t	t_to_sleep;
}			t_philo;

typedef struct s_data
{
}			t_data;

#endif
