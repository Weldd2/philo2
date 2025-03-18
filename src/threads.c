/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:40:42 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/18 15:33:53 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_join(t_data data, t_philo *philos, t_thread reaper)
{
	size_t	index;

	index = 0;
	while ((int)index < data->nb_philo)
	{
		pthread_join(philos[index]->thread, NULL);
		index++;
	}
	if (reaper != NULL)
		pthread_join(reaper, NULL);
}

void	start_philos(t_mgc mgc, t_data data, t_philo *philos, t_fork *forks)
{
	size_t	index;

	index = 0;
	while ((int)index < data->nb_philo)
	{
		philos[index] = philo_init(mgc, data, index);
		philos[index]->left_fork = &forks[index];
		philos[index]->right_fork = &forks[(index + 1) % data->nb_philo];
		if (pthread_create(&(philos[index]->thread), NULL, \
				philo_lifecycle, philos[index]) != 0)
			throw_thread_create(mgc);
		index++;
	}
}

void	start_philo(t_mgc mgc, t_data data, t_philo *philos, t_fork *forks)
{
	philos[0] = philo_init(mgc, data, 0);
	philos[0]->left_fork = &forks[0];
	philos[0]->right_fork = &forks[1];
	if (pthread_create(&(philos[0]->thread), NULL, \
			single_philo_lifecycle, philos[0]) != 0)
		throw_thread_create(mgc);
}

void	manage_threads(t_params params)
{
	t_philo		*philos;
	t_data		data;
	t_mgc		mgc;
	t_fork		*forks;
	t_thread	reaper;

	mgc = mgc_init();
	data = data_init(mgc, params);
	philos = mgc_alloc(mgc, sizeof(t_philo), params.nb_philo);
	forks = forks_init(mgc, params.nb_philo);
	if (data && data->nb_philo == 1)
	{
		start_philo(mgc, data, philos, forks);
		reaper = NULL;
	}
	else
	{
		start_philos(mgc, data, philos, forks);
		pthread_create(&(reaper), NULL, reaper_lifecycle, philos);
	}
	threads_join(data, philos, reaper);
	mgc_free(mgc);
	return ;
}
