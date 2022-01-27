/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:41:53 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/23 16:41:54 by wbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(t_data *data, int id, int min_fork, int max_fork)
{
	pthread_mutex_lock(&data->forks[min_fork]);
	print_message(data, id, "has taken a fork");
	if (data->params.number_of_philosophers == 1)
	{
		pthread_mutex_unlock(&data->forks[min_fork]);
		while (data->do_simulation)
			;
		return ;
	}
	pthread_mutex_lock(&data->forks[max_fork]);
	print_message(data, id, "has taken a fork");
	pthread_mutex_lock(&data->ph_mtx[id - 1]);
	data->philos_arr[id - 1].time_to_die = data->params.time_to_die;
	pthread_mutex_unlock(&data->ph_mtx[id - 1]);
	print_message(data, id, "is eating");
	ft_usleep(data->params.time_to_eat * 1000);
	(data->philos_arr[id - 1].count_time_to_eat)++;
}

void	try_to_eat(t_data *data, int id)
{
	int	min_fork;
	int	max_fork;

	max_fork = max(data->philos_arr[id - 1].left_fork,
			data->philos_arr[id - 1].right_fork);
	min_fork = min(data->philos_arr[id - 1].left_fork,
			data->philos_arr[id - 1].right_fork);
	do_eat(data, id, min_fork, max_fork);
	if (data->params.number_of_times_each_philosopher_must_eat != -1
		&& all_philo_eat_count_of_times(data))
	{
		print_message(data, -1, "all philosophers are full");
		data->do_simulation = 0;
	}
	pthread_mutex_unlock(&data->forks[max_fork]);
	pthread_mutex_unlock(&data->forks[min_fork]);
}

void	do_next_action(t_data *data, int id)
{
	if (data->philos_arr[id - 1].state == THINKING)
	{
		data->philos_arr[id - 1].state = EATING;
		try_to_eat(data, id);
	}
	else if (data->philos_arr[id - 1].state == EATING)
	{
		data->philos_arr[id - 1].state = SLEEPING;
		print_message(data, id, "is sleeping");
		ft_usleep(data->params.time_to_sleep * 1000);
	}
	else if (data->philos_arr[id - 1].state == SLEEPING)
	{
		data->philos_arr[id - 1].state = THINKING;
		print_message(data, id, "is thinking");
	}
}
