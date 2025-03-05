#include "philo.h"

void	throw_params_count(void)
{
	printf("Usage: ./philo <nb_philo> <time_to_die> <time_to_eat> "
		"<time_to_sleep> [<philo meal goal>]\n"
		"Times are expressed in milliseconds.\n");
	exit(EXIT_FAILURE);
}

void	throw_params_value(void)
{
	printf("Usage: ./philo <nb_philo> <time_to_die> <time_to_eat> "
		"<time_to_sleep> [<philo meal goal>]\n"
		"Values must be stricly positive.\n");
	exit(EXIT_FAILURE);
}

void	throw_mutex_init(t_mgc mgc)
{
	perror("mutex init failed");
	mgc_free(mgc);
	exit(EXIT_FAILURE);
}

void	throw_alloc_failed(t_mgc mgc)
{
	perror("memory allocation failed");
	mgc_free(mgc);
	exit(EXIT_FAILURE);
}

void	try_alloc(t_mgc mgc, void *ptr)
{
	if (!ptr)
		throw_alloc_failed(mgc);
}
