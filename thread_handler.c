/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:52:05 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/06/27 14:05:23 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *p_data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&p_data[i].thread_id, NULL,
				routine, &p_data[i]) != 0)
			printf("Error creating thread %d\n", i + 1);
		i++;
	}
}

void	join_threads(t_philo *p_data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_join(p_data[i].thread_id, NULL) != 0)
			fprintf(stderr, "Failed to join thread %d\n", i);
		i++;
	}
}

void	exec_rout(t_philo *philo)
{
	think(philo);
	take_forks(philo);
	eat(philo);
	release_forks(philo);
	sleep_philo(philo);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}
