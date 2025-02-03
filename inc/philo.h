/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:22:11 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/03 14:00:39 by tkonecny         ###   ########.fr       */
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
	size_t						time_to_die;
	size_t						time_to_eat;
	size_t						time_to_sleep;
	int							meals_required;
	unsigned long				start_time;
}								t_input;

typedef struct s_data
{
	pthread_mutex_t				*forks;
	pthread_mutex_t				print_lock;
	pthread_mutex_t				simulation_lock;
	t_philosophers				**philos;
	pthread_t					monitor;
	t_input						*input;
	int							is_running;
}								t_data;

typedef struct s_philosophers
{
	int							id;
	int							meals_eaten;
	size_t						last_meal_time;
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
void							print_actions(t_philosophers *philo,
									char *action);
void							better_sleeps(unsigned long time_in_ms);
void							print_action(t_philosophers *philo,
									char *action);

// Init
int								init_data(t_data *data, t_input *input);
int								init_thread(t_data *data);

// Error
int								error(int msg, t_data *data);

// Simulation
void							*philo_lifecycle(void *data);
void							*monitor(void *arg);

// Actions
void							put_fork(t_philosophers *philo);
void							eat(t_philosophers *philo);
void							take_fork(t_philosophers *philo);
void							think(t_philosophers *philo);
void							sleeps(t_philosophers *philo);

#endif
