/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:42:24 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/23 16:42:26 by wbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mtx_arr(pthread_mutex_t *mtx_arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&mtx_arr[i]);
		i++;
	}
	free(mtx_arr);
}

void	clear_data(t_data data)
{
	free(data.philos_arr);
	pthread_mutex_destroy(&data.id_mutex);
	pthread_mutex_destroy(&data.sim_mutex);
	destroy_mtx_arr(data.ph_mtx, data.params.number_of_philosophers);
	destroy_mtx_arr(data.forks, data.params.number_of_philosophers);
}
