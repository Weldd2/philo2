#include "philo.h"

void	philo_print(t_philo philo, char *msg)
{
	pthread_mutex_lock(&philo->data->mprint);
	printf("%lld %d %s\n", get_timestamp(), philo->index, msg);
	pthread_mutex_unlock(&philo->data->mprint);
}

void	philo_eat(t_philo philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		philo_print(philo, "is taking a fork");
		pthread_mutex_lock(&philo->right_fork);
		philo_print(philo, "is taking a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		philo_print(philo, "is taking a fork");
		pthread_mutex_lock(&philo->left_fork);
		philo_print(philo, "is taking a fork");
	}
	philo_print(philo, "is eating");
	set_meal_time(philo, get_timestamp());
	usleep(philo->data->time_to_eat * 1000);
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
		philo_print(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		philo_print(philo, "is thinking");
	}
	return (NULL);
}