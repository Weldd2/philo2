/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:40:14 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/05 18:17:06 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	philo_init(t_mgc mgc, t_data data, int index)
{
	t_philo	philo;

	philo = mgc_alloc(mgc, sizeof(t_philo_), 1);
	try_alloc(mgc, philo);
	philo->data = data;
	philo->index = index;
	philo->meal_count = 0;
	if (pthread_mutex_init(&philo->mlast_meal_time, NULL) != 0)
		throw_mutex_init(mgc);
	philo->last_meal_time = get_timestamp();
	return (philo);
}

t_data	data_init(t_mgc mgc, t_params params)
{
	t_data	data;

	data = mgc_alloc(mgc, sizeof(t_data_), 1);
	try_alloc(mgc, data);
	data->meal_goal = params.meal_goal;
	data->nb_philo = params.nb_philo;
	data->time_to_die = params.time_to_die;
	data->time_to_eat = params.time_to_eat;
	data->time_to_sleep = params.time_to_sleep;
	data->stop_flag = false;
	if (pthread_mutex_init(&data->mstop_flag, NULL) != 0)
		throw_mutex_init(mgc);
	if (pthread_mutex_init(&data->mprint, NULL) != 0)
		throw_mutex_init(mgc);
	return (data);
}

t_fork	*forks_init(t_mgc mgc, int nb_forks)
{
	t_fork	*forks;
	size_t	index;

	index = 0;
	forks = mgc_alloc(mgc, sizeof(t_fork), nb_forks);
	try_alloc(mgc, forks);
	while ((int)index < nb_forks)
	{
		forks[index].is_free = true;
		if (pthread_mutex_init(&(forks[index].fork), NULL) != 0)
			throw_mutex_init(mgc);
		if (pthread_mutex_init(&(forks[index].mis_free), NULL) != 0)
			throw_mutex_init(mgc);
		index++;
	}
	return (forks);
}
