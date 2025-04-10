/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:16:31 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/10 22:30:25 by antoinemura      ###   ########.fr       */
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

void	philo_eat(t_philo philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork);
		philo_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
		philo_print(philo, "has taken a fork");
	}
	philo_print(philo, "is eating");
	set_meal_time(philo, get_timestamp());
	ft_msleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*single_philo_lifecycle(void *void_philo)
{
	t_philo	philo;

	philo = (t_philo)void_philo;
	pthread_mutex_lock(&philo->left_fork->fork);
	philo_print(philo, "has taken a fork");
	ft_msleep(philo->data->time_to_die);
	return (NULL);
}

void	*philo_lifecycle(void *void_philo)
{
	t_philo	philo;
	size_t	meal_counter;

	philo = (t_philo)void_philo;
	meal_counter = 0;
	if (philo->index % 2 == 1)
		ft_msleep(5);
	while (!get_stop_flag(philo->data))
	{
		philo_eat(philo);
		meal_counter++;
		if (philo->data->meal_goal != 0
			&& meal_counter == philo->data->meal_goal)
			increment_finished_count(philo->data);
		philo_print(philo, "is sleeping");
		ft_msleep(philo->data->time_to_sleep);
		philo_print(philo, "is thinking");
	}
	return (NULL);
}
