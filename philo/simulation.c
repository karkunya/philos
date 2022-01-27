/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:43:07 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/23 16:43:08 by wbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watcher_routine(void *arg)
{
	t_data	*data;
	int		id;
	int		i;

	data = ((t_philo_info *)arg)->data;
	id = ((t_philo_info *)arg)->id;
	while (data->do_simulation)
	{
		pthread_mutex_lock(&data->ph_mtx[id - 1]);
		(data->philos_arr[id - 1].time_to_die)--;
		if (data->philos_arr[id - 1].time_to_die == 0)
		{
			print_message(data, id, "died");
			data->do_simulation = 0;
			i = 0;
			while (i <= data->params.number_of_philosophers)
				pthread_mutex_unlock(&data->forks[i++]);
			pthread_mutex_unlock(&data->ph_mtx[id - 1]);
			return (NULL);
		}
		pthread_mutex_unlock(&data->ph_mtx[id - 1]);
		ft_usleep(1000);
	}
	return (NULL);
}

void	act(t_data *data, t_philo_info philo_info)
{
	pthread_t		tid;

	if ((pthread_create(&tid, NULL, watcher_routine, (void *)&philo_info)) != 0)
	{
		printf("Error: System error happened");
		pthread_mutex_unlock(&data->id_mutex);
		data->do_simulation = 0;
		return ;
	}
	pthread_mutex_unlock(&data->id_mutex);
	while (data->do_simulation)
		do_next_action(data, philo_info.id);
	pthread_join(tid, NULL);
}

void	*philo_routine(void *arg)
{
	t_philo_info	philo_info;
	t_data			*data;
	static int		id = 1;
	int				local_id;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->id_mutex);
	if (id > data->params.number_of_philosophers)
	{
		id = data->params.number_of_philosophers
			- (data->params.number_of_philosophers % 2);
	}
	local_id = id;
	if (id % 2 == 0)
	{
		data->philos_arr[id - 1].state = SLEEPING;
		id -= 2;
	}
	else
		id += 2;
	philo_info.data = data;
	philo_info.id = local_id;
	act(data, philo_info);
	return (NULL);
}

int	simulation(t_data data, pthread_t *tid)
{
	int	i;

	i = 0;
	while (i < data.params.number_of_philosophers)
	{
		if ((pthread_create(&tid[i], NULL, &philo_routine, (void *)&data)) != 0)
		{
			printf("Error: System error happened");
			data.do_simulation = 0;
			while (i-- >= 0)
				pthread_join(tid[i], NULL);
			pthread_join(tid[data.params.number_of_philosophers], NULL);
			free(tid);
			clear_data(data);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data.params.number_of_philosophers)
		pthread_join(tid[i++], NULL);
	free(tid);
	clear_data(data);
	return (0);
}

int	start_simulation(t_params params)
{
	t_data			data;
	pthread_t		*tid;

	tid = (pthread_t *)malloc(sizeof(pthread_t)
			* params.number_of_philosophers);
	if (tid == NULL)
	{
		printf("Error: Cannot allocate memory");
		return (1);
	}
	if ((init_data(&data, params)) == -1)
	{
		printf("Error: System error happened");
		free(tid);
		return (1);
	}
	return (simulation(data, tid));
}
