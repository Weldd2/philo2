/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:47:29 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/10 15:51:08 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	increment_finished_count(t_data data)
{
	pthread_mutex_lock(&data->mfinished_count);
	data->finished_count++;
	pthread_mutex_unlock(&data->mfinished_count);
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
