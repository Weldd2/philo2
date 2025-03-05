#include "philo.h"

void	set_stop_flag(t_data data, bool value)
{
	pthread_mutex_lock(&data->mstop_flag);
	data->stop_flag = value;	
	pthread_mutex_unlock(&data->mstop_flag);
}

bool	get_stop_flag(t_data data)
{
	bool	val;

	pthread_mutex_lock(&data->mstop_flag);
	val = data->stop_flag;
	pthread_mutex_unlock(&data->mstop_flag);
	return (val);
}

void	set_meal_time(t_philo philo, t_timestamp timestamp)
{
	pthread_mutex_lock(&philo->mlast_meal_time);
	philo->last_meal_time = timestamp;	
	pthread_mutex_unlock(&philo->mlast_meal_time);
}

t_timestamp	get_meal_time(t_philo philo)
{
	t_timestamp	val;

	pthread_mutex_lock(&philo->mlast_meal_time);
	val = philo->last_meal_time;
	pthread_mutex_unlock(&philo->mlast_meal_time);
	return (val);
}
