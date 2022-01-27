/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:43:17 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/23 16:43:18 by wbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int	result;

	result = 0;
	while (*s)
	{
		result *= 10;
		result += (*s++) - '0';
	}
	return (result);
}

void	ft_usleep(int usec)
{
	struct timeval	start_time;
	struct timeval	iteration_time;
	int				sleep_time;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		usleep(5);
		gettimeofday(&iteration_time, NULL);
		sleep_time = ((iteration_time.tv_sec - start_time.tv_sec) * 1000)
			+ (iteration_time.tv_usec - start_time.tv_usec);
		if (sleep_time >= usec)
			break ;
	}
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(ft_isdigit(s[i++])))
			return (0);
	}
	return (i > 0);
}

int	all_philo_eat_count_of_times(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.number_of_philosophers)
	{
		if (data->philos_arr[i].count_time_to_eat
			< data->params.number_of_times_each_philosopher_must_eat)
			return (0);
		i++;
	}
	return (1);
}
