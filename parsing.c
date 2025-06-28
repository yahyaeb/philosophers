/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 06:19:58 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/06/27 13:08:27 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(int argc, char **argv, t_data *data)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6 && argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
}

int	parse_args(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo num1 num2 num3 num4 [num5]\n");
		return (1);
	}
	while (i < argc)
	{
		if (!is_within_range(argv[i]))
		{
			printf("Invalid input: out of int range or invalid characters.\n");
			return (-1);
		}
		i++;
	}
	init_philos(argc, argv, data);
	if (data->number_of_philosophers <= 0)
	{
		printf("At least one philosopher is required.\n");
		return (-1);
	}
	return (0);
}
