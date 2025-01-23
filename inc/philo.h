/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:22:11 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/23 13:16:54 by tkonecny         ###   ########.fr       */
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

# define ERROR 1
# define SUCCESS 0

typedef struct s_philosophers	t_philosophers;

typedef struct s_input
{
	int							number_of_philos;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							meals_required;
}								t_input;

typedef struct s_data
{
	t_input						*input;
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
int								numbercheck(char *argv[], int argc);
int								ft_atoi(const char *nptr);
int								free_all(t_data *data);
int								inputload(char **argv, t_input *input, int argc);

// Init
int								init(char **argv, t_data *data);

#endif
