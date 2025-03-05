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

t_mutex	*forks_init(t_mgc mgc, int nb_forks)
{
	t_mutex	*forks;
	size_t	index;

	index = 0;
	forks = mgc_alloc(mgc, sizeof(t_mutex), nb_forks);	
	try_alloc(mgc, forks);
	while ((int)index < nb_forks)
	{
		if (pthread_mutex_init(&forks[index], NULL) != 0)
			throw_mutex_init(mgc);
		index++;
	}
	return (forks);
}

void	start_threads(t_params params)
{
	size_t	index;
	t_philo	*philos;
	t_data	data;
	t_mgc	mgc;
	t_mutex	*forks;
	
	index = 0;
	mgc = mgc_init();
	data = data_init(mgc, params);
	philos = mgc_alloc(mgc, sizeof(t_philo), params.nb_philo);
	forks = forks_init(mgc, params.nb_philo);
	// TODO init forks
	while ((int)index < params.nb_philo)
	{
		philos[index] = philo_init(mgc, data, index);
		philos[index]->left_fork = forks[index];
		philos[index]->right_fork = forks[(index + 1) % params.nb_philo];
		pthread_create(&(philos[index]->thread), NULL, philo_lifecycle, philos[index]);
		index++;
	}
	t_thread reaper;
	pthread_create(&(reaper), NULL, reaper_lifecycle, philos);
	index = 0;
	while ((int)index < params.nb_philo)
	{
		pthread_join(philos[index]->thread, NULL);
		index++;
	}
	pthread_join(reaper, NULL);
	mgc_free(mgc);
	return ;
}
