/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:22:11 by tkonecny          #+#    #+#             */
/*   Updated: 2025/01/14 18:48:05 by tkonecny         ###   ########.fr       */
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

typedef struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				is_running;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			lasr_meal_time;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
}					t_philosophers;

// Utils
int					argcheck(char *argv[]);
int					ft_atoi(const char *nptr);

// Init
int					init(char **argv, t_data *data, int argc);

#endif
