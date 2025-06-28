/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 05:35:24 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/06/27 17:59:25 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	exec_fork(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	smart_sleep(philo->data->time_to_sleep, philo->data);
	print_action(philo, "died");
	pthread_mutex_lock(&philo->data->stop_mutex);
	philo->data->stop_simulation = 1;
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->number_of_philosophers == 1)
		{
			exec_fork(philo);
			return (NULL);
		}
		usleep(philo->id * 50);
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop_simulation)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		exec_rout(philo);
	}
	return (NULL);
}

void	lock_thesimulation(t_philo	*philos,
		t_data *data, long timestamp, int i)
{
	pthread_mutex_unlock(&data->meal_mutex);
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	timestamp = get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n", timestamp, philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
}
int	check_all_full(t_philo *philos, t_data *data)
{
	int	full = 0;
	int	i;

	if (data->number_of_times_each_philosopher_must_eat <= 0)
		return (0);

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (philos[i].meals_eaten >= data->number_of_times_each_philosopher_must_eat)
			full++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (full == data->number_of_philosophers)
	{
		usleep(1000);
		pthread_mutex_lock(&data->stop_mutex);
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		return (1); // simulation should stop
	}
	return (0); // continue simulation
}

int	check_philosophers(t_philo *philos, t_data *data)
{
	long	now;
	int		i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->meal_mutex);
		now = get_time_in_ms();
		if (now - philos[i].last_meal_time > data->time_to_die)
		{
			lock_thesimulation(philos, data, now, i);
			return (1); // someone died
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0); // no one died
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos = (t_philo *)arg;
	t_data	*data = philos[0].data;

	while (1)
	{
		if (check_philosophers(philos, data))
			return (NULL);
		if (check_all_full(philos, data))
			return (NULL);
		usleep(2000);
	}
	return (NULL);
}

// void	*monitor_routine(void *arg)
// {
// 	t_philo	*philos;
// 	t_data	*data;
// 	long	now;
// 	long	timestamp;
// 	int		full;
// 	int		i;

// 	philos = (t_philo *)arg;
// 	data = philos[0].data;
// 	timestamp = 0;
// 	while (1)
// 	{
// 		full = 0;
// 		i = 0;
// 		while (i < data->number_of_philosophers)
// 		{
// 			pthread_mutex_lock(&data->meal_mutex);
// 			now = get_time_in_ms();
// 			if (now - philos[i].last_meal_time > data->time_to_die)
// 			{
// 				lock_thesimulation(philos, data, timestamp, i);
// 				return (NULL);
// 			}
// 			if (data->number_of_times_each_philosopher_must_eat > 0
// 				&& philos[i].meals_eaten
// 				>= data->number_of_times_each_philosopher_must_eat)
// 				full++;
// 			pthread_mutex_unlock(&data->meal_mutex);
// 			i++;
// 		}
// 		if (data->number_of_times_each_philosopher_must_eat > 0
// 			&& full == data->number_of_philosophers)
// 		{
// 			usleep(1000);
// 			pthread_mutex_lock(&data->stop_mutex);
// 			data->stop_simulation = 1;
// 			pthread_mutex_unlock(&data->stop_mutex);
// 			return (NULL);
// 		}
// 		usleep(2000);
// 	}
// 	return (NULL);
// }

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;
	int		i;

	if (parse_args(argc, argv, &data))
		return (1);
	philos = malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!philos)
		return (printf("Malloc failed\n"));
	data.forks = malloc(sizeof(pthread_mutex_t) * data.number_of_philosophers);
	if (!data.forks)
	{
		fprintf(stderr, "Fork malloc failed\n");
		free(philos);
		return (1);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data.meal_mutex, NULL);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		philos[i].last_meal_time = get_time_in_ms();
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].data = &data;
		philos[i].left_fork = &data.forks[i];
		philos[i].right_fork = &data.forks[(i + 1)
			% data.number_of_philosophers];
		i++;
	}
	pthread_mutex_init(&data.print_mutex, NULL);
	pthread_mutex_init(&data.stop_mutex, NULL);
	data.start_time = get_time_in_ms();
	i = 0;
	while (i < data.number_of_philosophers)
	{
		philos[i].last_meal_time = data.start_time;
		i++;
	}
	pthread_create(&philos->data->monitor, NULL, monitor_routine, philos);
	create_threads(philos, data.number_of_philosophers);
	usleep(50);
	join_threads(philos, data.number_of_philosophers);
	pthread_join(data.monitor, NULL);
	// usleep(500);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.stop_mutex);
	pthread_mutex_destroy(&data.meal_mutex);
	free(philos);
	free(data.forks);
	return (0);
}
