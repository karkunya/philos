/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:42:52 by wbeach            #+#    #+#             */
/*   Updated: 2022/01/23 16:42:54 by wbeach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define THINKING 1
# define EATING 2
# define SLEEPING 3

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>

typedef struct s_philosopher {
	int	state;
	int	time_to_die;
	int	left_fork;
	int	right_fork;
	int	count_time_to_eat;
}				t_philosopher;

typedef struct s_params {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}				t_params;

typedef struct s_data {
	t_params		params;
	t_philosopher	*philos_arr;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*ph_mtx;
	struct timeval	start_time;
	int				do_simulation;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	sim_mutex;
}				t_data;

typedef struct s_philo_info {
	t_data	*data;
	int		id;
}				t_philo_info;

//utils
void		ft_usleep(int usec);
int			ft_atoi(char *s);
int			ft_isdigit(char c);
int			ft_isnumber(char *s);
int			all_philo_eat_count_of_times(t_data *data);
int			min(int a, int b);
int			max(int a, int b);

//philo
t_params	*init_params(int argc, char **argv);
void		set_param(t_params *params, int i, int value);
void		set_default_params(t_params *params);

//print
void		print_message(t_data *data, int id, char *message);

//init_data
int			init_data(t_data *data, t_params params);

//clear_data
void		destroy_mtx_arr(pthread_mutex_t *mtx_arr, int len);
void		clear_data(t_data data);

//simulation
int			start_simulation(t_params params);
int			simulation(t_data data, pthread_t *tid);
void		*watcher_routine(void *arg);
void		act(t_data *data, t_philo_info philo_info);
void		*philo_routine(void *arg);

//actions
void		do_next_action(t_data *data, int id);

#endif
