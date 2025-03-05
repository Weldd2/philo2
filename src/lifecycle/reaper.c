/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:46:52 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/05 16:04:47 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper_lifecycle(void *void_philos)
{
	int		index;
	t_data	data;
	t_philo	*philos;

	index = 0;
	philos = (t_philo *)void_philos;
	data = philos[0]->data;
	while (index < data->nb_philo)
	{
		usleep(1000);
		if (get_timestamp() >= get_meal_time(philos[index]) + data->time_to_die)
		{
			if (get_stop_flag(data))
				return (NULL);
			philo_print(philos[index], "died");
			set_stop_flag(data, true);
			return (NULL);
		}
		index++;
		index %= data->nb_philo;
	}
	return (NULL);
}
