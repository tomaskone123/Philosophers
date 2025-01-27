/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:22:11 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/27 15:00:24 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <aio.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR 1
# define SUCCESS 0

typedef struct s_philosophers	t_philosophers;

typedef enum e_msg
{
	INCORRECT_MALLOC = 1,
	INCORRECT_MUTEX = 2,
	INCORRECT_THREAD = 3,
}								t_msg;

typedef struct s_input
{
	int							number_of_philos;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							meals_required;
	unsigned long				start_time;
}								t_input;

typedef struct s_data
{
	t_input						*input;
	pthread_mutex_t				*forks;
	pthread_mutex_t				print_lock;
	int							is_running;
	t_philosophers				**philos;
}								t_data;

typedef struct s_philosophers
{
	int							id;
	int							meals_eaten;
	size_t						lasr_meal_time;
	pthread_t					thread;
	pthread_mutex_t				meal_lock;
	t_data						*data;
	t_input						*input;
}								t_philosophers;

// Utils
int								numbercheck(char *argv[], int argc);
int								ft_atoi(const char *nptr);
void							free_all(t_data *data);
int								inputload(char **argv, t_input *input,
									int argc);
unsigned long					get_time_in_ms(void);
// Init
int								init_data(t_data *data, t_input *input);
int								init_thread(t_data *data);

// Error
int								error(int msg, t_data *data);

// Simulation
void							*philo_lifecycle(void *data);

#endif
