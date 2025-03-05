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

typedef pthread_mutex_t t_mutex;
typedef pthread_t t_thread;
typedef long long int t_timestamp;

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
}	t_data_, *t_data;

typedef struct s_philo
{
	int			index;
	int			meal_count;
	t_thread	thread;
	t_mutex		left_fork;
	t_mutex		right_fork;
	t_data		data;
	t_timestamp	last_meal_time;
	t_mutex		mlast_meal_time;
}	t_philo_, *t_philo;

t_timestamp	get_timestamp(void);
void		start_threads(t_params params);
void		*philo_lifecycle(void *void_philo);
void		set_stop_flag(t_data data, bool value);
bool		get_stop_flag(t_data data);
void		set_meal_time(t_philo philo, t_timestamp timestamp);
t_timestamp	get_meal_time(t_philo philo);
void		*reaper_lifecycle(void *void_philos);
void		philo_print(t_philo philo, char *msg);

#endif