#ifndef PARSING_H
# define PARSING_H

# include "stdbool.h"

typedef struct s_params
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_goal;
}	t_params;

t_params	get_params(int argc, char **argv);

#endif