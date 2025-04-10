/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:00:11 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/10 22:32:56 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	_has_to_stop(t_data data)
{
	bool	has_to_stop;

	pthread_mutex_lock(&data->mfinished_count);
	has_to_stop = (data->finished_count == data->nb_philo);
	pthread_mutex_unlock(&data->mfinished_count);
	return (has_to_stop);
}

void	*reaper_lifecycle(void *void_philos)
{
	int		index;
	t_data	data;
	t_philo	*philos;

	index = 0;
	philos = (t_philo *)void_philos;
	data = philos[0]->data;
	while (1)
	{
		ft_msleep(1);
		if (get_timestamp() >= get_meal_time(philos[index]) + data->time_to_die)
		{
			philo_print(philos[index], "died");
			set_stop_flag(data, true);
			return (NULL);
		}
		if (_has_to_stop(data))
			set_stop_flag(data, true);
		index++;
		index %= data->nb_philo;
	}
	return (NULL);
}
