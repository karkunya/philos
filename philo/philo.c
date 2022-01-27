/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:42:40 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/23 16:42:42 by wbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_default_params(t_params *params)
{
	params->number_of_philosophers = -1;
	params->time_to_die = -1;
	params->time_to_eat = -1;
	params->time_to_sleep = -1;
	params->number_of_times_each_philosopher_must_eat = -1;
}

void	set_param(t_params *params, int i, int value)
{
	if (i == 1)
		params->number_of_philosophers = value;
	else if (i == 2)
		params->time_to_die = value;
	else if (i == 3)
		params->time_to_eat = value;
	else if (i == 4)
		params->time_to_sleep = value;
	else if (i == 5)
		params->number_of_times_each_philosopher_must_eat = value;
}

t_params	*init_params(int argc, char **argv)
{
	static t_params	params;
	int				i;
	int				value;

	set_default_params(&params);
	i = 1;
	while (i < argc)
	{
		if (!(ft_isnumber(argv[i])))
		{
			printf("Error: is negative or not numeric argument");
			return (NULL);
		}
		value = ft_atoi(argv[i]);
		if (value == 0)
		{
			printf("Error: null argument");
			return (NULL);
		}
		set_param(&params, i, ft_atoi(argv[i]));
		i++;
	}
	return (&params);
}

int	main(int argc, char **argv)
{
	t_params	*params;
	int			ret;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments");
		return (1);
	}
	params = init_params(argc, argv);
	if (params == NULL)
		return (1);
	ret = start_simulation(*params);
	return (ret);
}
