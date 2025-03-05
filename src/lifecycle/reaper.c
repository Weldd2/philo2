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
		if (get_timestamp() >= get_meal_time(philos[index]) + data->time_to_die) 
		{
			set_stop_flag(data, true);
			return (NULL);
		}
		index++;
		index %= data->nb_philo;
	}
	return (NULL);
}
