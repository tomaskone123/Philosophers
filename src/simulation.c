/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:14 by tkonecny          #+#    #+#             */
/*   Updated: 2025/02/17 13:26:40 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*only_one_philo(t_philosophers *philo)
{
	print_action(philo, "has taken a fork");
	delay(philo->input->time_to_die);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	return (NULL);
}

void	*philo_lifecycle(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->input->meals_required == 0)
		return (NULL);
	if (philo->data->input->number_of_philos == 1)
		return (only_one_philo(philo));
	if (philo->id % 2 == 0)
	{
		print_action(philo, "DELAY");
		delay(philo->input->time_to_eat / 2);
	}
	if (philo->data->input->number_of_philos % 2 == 1 && philo->id == philo->data->input->number_of_philos)
	{
		print_action(philo, "DELAY2");
		delay(philo->input->time_to_eat / 2);
	}
	while (1)
	{
		if (!check_running(philo))
			return (NULL);
		philo_actions(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->input->number_of_philos)
		{
			pthread_mutex_lock(&data->philos[i]->meal_lock);
			pthread_mutex_lock(&data->data_lock);
			if (data->philos[i]->meals_eaten > 0 && get_time_in_ms()
				- data->philos[i]->last_meal_time > data->input->time_to_die)
				return (stopprocess(data, i));
			if (data->full_philos == data->input->number_of_philos)
				return (stopprocess(data, i));
			pthread_mutex_unlock(&data->data_lock);
			pthread_mutex_unlock(&data->philos[i]->meal_lock);
			i++;
		}
		delay(1);
	}
	return (NULL);
}


static char *get_color(int id)
{
	const char *colors[] = {
        "\033[0;31m", // Red for index 0
        "\033[0;32m", // Green for index 1
        "\033[0;33m", // Yellow for index 2
        "\033[0;34m", // Blue for index 3
        "\033[0;35m", // Magenta for index 4
        "\033[0;36m"  // Cyan for index 5
    };
    
    // Default to reset color if index is out of bounds
   return (id >= 0 && id < 6) ? colors[id] : "\033[0m";
}

void	print_action(t_philosophers *philo, char *action)
{
	char *color = get_color(philo->id);
	static int ts = 0;
	int ts2 = get_time_in_ms();
	if (ts != ts2)
	{
		ts = ts2;
		printf("\n");
	}

	if (!check_running(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	if (ft_strncmp(action, "has eaten enough", 16) == 0)
		printf("%s%lu\tALL MEALS EATEN\033[0m\n", color, get_time_in_ms() - philo->data->input->start_time);
	else
		printf("%s%lu\t%d %s\033[0m\n", color, get_time_in_ms() - philo->data->input->start_time, philo->id, action);

	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_fork(t_philosophers *philo, int fork)
{
	
	char *color = get_color(philo->id);

	pthread_mutex_lock(&philo->data->print_lock);

	printf("%s%lu\t%d took fork idx %i\033[0m\n",color, get_time_in_ms()
		- philo->data->input->start_time, philo->id, fork);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	delay(int delayed_time)
{
	unsigned long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < (unsigned long)delayed_time)
		usleep(1);
}
