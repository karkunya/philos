/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:43:00 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/23 16:43:02 by wbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_data *data, int id, char *message)
{
	uintmax_t		timestamp;
	struct timeval	current_time;

	pthread_mutex_lock(&data->sim_mutex);
	if (data->do_simulation == 0)
	{
		pthread_mutex_unlock(&data->sim_mutex);
		return ;
	}
	gettimeofday(&current_time, NULL);
	timestamp = (uintmax_t)((current_time.tv_sec - data->start_time.tv_sec)
			* 1000
			+ (current_time.tv_usec - data->start_time.tv_usec)
			/ 1000);
	if (id == -1)
		printf("%ju %s\n", timestamp, message);
	else
		printf("%ju %d %s\n", timestamp, id, message);
	pthread_mutex_unlock(&data->sim_mutex);
}
