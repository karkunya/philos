/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:42:31 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/23 16:42:34 by wbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_philosopher *philos_arr, t_params params)
{
	int	i;

	i = 0;
	while (i < params.number_of_philosophers)
	{
		philos_arr[i].state = THINKING;
		philos_arr[i].time_to_die = params.time_to_die;
		philos_arr[i].left_fork = i;
		philos_arr[i].right_fork = (i + 1) % params.number_of_philosophers;
		philos_arr[i].count_time_to_eat = 0;
		i++;
	}
	return (0);
}

int	init_data1(t_data *data)
{
	data->philos_arr = (t_philosopher *)malloc(sizeof(t_philosopher)
			* data->params.number_of_philosophers);
	if (data->philos_arr == NULL)
		return (-1);
	if ((init_philosophers(data->philos_arr, data->params)) == -1)
	{
		free(data->philos_arr);
		return (-1);
	}
	data->ph_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->params.number_of_philosophers);
	if (data->ph_mtx == NULL)
	{
		free(data->philos_arr);
		return (-1);
	}
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->params.number_of_philosophers);
	if (data->forks == NULL)
	{
		free(data->philos_arr);
		free(data->ph_mtx);
		return (-1);
	}
	return (0);
}

int	init_data2(t_data *data)
{
	if ((pthread_mutex_init(&data->id_mutex, NULL)) != 0)
	{
		free(data->philos_arr);
		free(data->ph_mtx);
		free(data->forks);
		return (-1);
	}
	if ((pthread_mutex_init(&data->sim_mutex, NULL)) != 0)
	{
		free(data->philos_arr);
		free(data->ph_mtx);
		free(data->forks);
		pthread_mutex_destroy(&data->id_mutex);
		return (-1);
	}
	return (0);
}

int	init_data3(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.number_of_philosophers)
	{
		if ((pthread_mutex_init(&data->ph_mtx[i], NULL)) != 0)
		{
			free(data->philos_arr);
			destroy_mtx_arr(data->forks, i - 1);
			destroy_mtx_arr(data->ph_mtx, i);
			pthread_mutex_destroy(&data->sim_mutex);
			pthread_mutex_destroy(&data->id_mutex);
			return (-1);
		}
		if ((pthread_mutex_init(&data->forks[i++], NULL)) != 0)
		{
			free(data->philos_arr);
			destroy_mtx_arr(data->forks, i - 1);
			destroy_mtx_arr(data->ph_mtx, i);
			pthread_mutex_destroy(&data->id_mutex);
			pthread_mutex_destroy(&data->sim_mutex);
			return (-1);
		}
	}
	return (0);
}

int	init_data(t_data *data, t_params params)
{
	static struct timeval	start_time;

	data->params = params;
	data->do_simulation = 1;
	if ((init_data1(data)) == -1)
		return (-1);
	if ((init_data2(data)) == -1)
		return (-1);
	if ((init_data3(data)) == -1)
		return (-1);
	gettimeofday(&start_time, NULL);
	data->start_time = start_time;
	return (0);
}
