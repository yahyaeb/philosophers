/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:06:16 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/06/27 14:07:54 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(long duration_ms, t_data *data)
{
	long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < duration_ms)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		usleep(100);
	}
}

void	print_action(t_philo *philo, char *action)
{
	int		stop;
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->stop_mutex);
	stop = philo->data->stop_simulation;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	if (!stop)
	{
		timestamp = get_time_in_ms() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_action(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
}

void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
}
