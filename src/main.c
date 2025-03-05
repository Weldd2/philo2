#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	params;

	params = get_params(argc, argv);
	start_threads(params);
	return (0);
}
