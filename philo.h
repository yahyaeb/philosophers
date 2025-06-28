/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 06:20:36 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/06/27 16:10:08 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "./libft/libft.h"

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				argv;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long long		start_time;
	pthread_mutex_t	meal_mutex;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				stop_simulation;
	pthread_mutex_t	stop_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

int		parse_args(int argc, char **argv, t_data *data);
void	create_threads(t_philo *p_data, int n);
void	join_threads(t_philo *p_data, int n);
int		is_within_range(char *str);
void	*routine(void *arg);
long	get_time_in_ms(void);
void	smart_sleep(long duration_ms, t_data *data);
void	print_action(t_philo *philo, char *action);
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	exec_rout(t_philo *philo);
void	*routine(void *arg);
void	*monitor_routine(void *arg);
void	init_philos(int argc, char **argv, t_data *data);
void	exec_fork(t_philo *philo);
