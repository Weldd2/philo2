/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:46:42 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/05 16:01:15 antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo philo, char *msg)
{
	pthread_mutex_lock(&philo->data->mprint);
	if (!get_stop_flag(philo->data))
		printf("%lld %d %s\n", get_timestamp(), philo->index, msg);
	pthread_mutex_unlock(&philo->data->mprint);
}

bool	can_take_forks(t_philo philo)
{
	bool	r;

	pthread_mutex_lock(&philo->left_fork->mis_free);
	pthread_mutex_lock(&philo->right_fork->mis_free);
	r = philo->left_fork->is_free && philo->right_fork->is_free;
	if (!r)
	{
		pthread_mutex_unlock(&philo->left_fork->mis_free);
		pthread_mutex_unlock(&philo->right_fork->mis_free);
	}
	return (r);
}

void	philo_eat(t_philo philo)
{
	while (!can_take_forks(philo))
		usleep(10);
	pthread_mutex_lock(&philo->right_fork->fork);
	philo_print(philo, "is taking his right fork");
	pthread_mutex_lock(&philo->left_fork->fork);
	philo_print(philo, "is taking his left fork");
	philo_print(philo, "is eating");
	set_meal_time(philo, get_timestamp());
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->mis_free);
	pthread_mutex_unlock(&philo->right_fork->mis_free);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*philo_lifecycle(void *void_philo)
{
	t_philo	philo;
	size_t	meal_counter;

	philo = (t_philo)void_philo;
	meal_counter = 0;
	while (!get_stop_flag(philo->data))
	{
		philo_eat(philo);
		meal_counter++;
		if (philo->data->meal_goal != 0
			&& meal_counter == philo->data->meal_goal)
		{
			set_stop_flag(philo->data, true);
			break ;
		}
		philo_print(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		philo_print(philo, "is thinking");
	}
	return (NULL);
}
