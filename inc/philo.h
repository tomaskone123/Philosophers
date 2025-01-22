/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:22:11 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/22 17:03:22 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include <aio.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philosophers	t_philosophers;

typedef struct s_data
{
	int							number_of_philos;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							meals_required;
	pthread_mutex_t				*forks;
	pthread_mutex_t				print_lock;
	int							is_running;
	t_philosophers				*philos;
}								t_data;

typedef struct s_philosophers
{
	int							id;
	int							meals_eaten;
	size_t						lasr_meal_time;
	t_data						*data;
	pthread_t					thread;
	pthread_mutex_t				meal_lock;
}								t_philosophers;

// Utils
int								argcheck(char *argv[], int argc);
int								ft_atoi(const char *nptr);
int								free_all(t_data **data);

// Init
int								init(char **argv, t_data **data);

#endif
