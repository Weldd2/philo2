#include "philo.h"

void	philo_eat(t_philo philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		printf("%lld %d is taking a fork\n", get_timestamp(), philo->index);
		pthread_mutex_lock(&philo->right_fork);
		printf("%lld %d is taking a fork\n", get_timestamp(), philo->index);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		printf("%lld %d is taking a fork\n", get_timestamp(), philo->index);
		pthread_mutex_lock(&philo->left_fork);
		printf("%lld %d is taking a fork\n", get_timestamp(), philo->index);
	}
	printf("%lld %d is eating\n", get_timestamp(), philo->index);
	set_meal_time(philo, get_timestamp());
	usleep(philo->data->time_to_eat *  1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
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
		if (philo->data->meal_goal != 0 && meal_counter == philo->data->meal_goal)
		{
			set_stop_flag(philo->data, true);
			break ;
		}
		printf("%lld %d is sleeping\n", get_timestamp(), philo->index);
		usleep(philo->data->time_to_sleep *  1000);
		printf("%lld %d is thinking\n", get_timestamp(), philo->index);
	}
	// doing nothing
	return (NULL);
}