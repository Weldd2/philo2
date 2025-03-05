/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:39:13 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/05 17:50:50 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>
# include "mgc.h"
# include "parsing.h"
# include "error.h"

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef long long int	t_timestamp;

typedef struct s_data
{
	t_mutex	mstop_flag;
	bool	stop_flag;
	t_mutex	mprint;
	size_t	meal_goal;
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}	t_data_;

typedef t_data_*		t_data;

typedef struct s_fork
{
	t_mutex	fork;
	bool	is_free;
	t_mutex	mis_free;
}	t_fork;

typedef struct s_philo
{
	int			index;
	int			meal_count;
	t_thread	thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_data		data;
	t_timestamp	last_meal_time;
	t_mutex		mlast_meal_time;
}	t_philo_;

typedef t_philo_*		t_philo;

t_timestamp	get_timestamp(void);
void		manage_threads(t_params params);
void		*philo_lifecycle(void *void_philo);
void		set_stop_flag(t_data data, bool value);
bool		get_stop_flag(t_data data);
void		set_meal_time(t_philo philo, t_timestamp timestamp);
t_timestamp	get_meal_time(t_philo philo);
void		*reaper_lifecycle(void *void_philos);
void		philo_print(t_philo philo, char *msg);
t_philo		philo_init(t_mgc mgc, t_data data, int index);
t_data		data_init(t_mgc mgc, t_params params);
// t_mutex		*forks_init(t_mgc mgc, int nb_forks);
t_fork		*forks_init(t_mgc mgc, int nb_forks);

#endif