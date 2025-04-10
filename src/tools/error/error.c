/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:47:41 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/10 17:59:17 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	throw_params_count(void)
{
	fprintf(stderr, "Usage: ./philo <nb_philo> <time_to_die> <time_to_eat> "
		"<time_to_sleep> [<philo meal goal>]\n"
		"Times are expressed in milliseconds.\n");
	exit(EXIT_FAILURE);
}

void	throw_params_value(void)
{
	fprintf(stderr, "Usage: ./philo <nb_philo> <time_to_die> <time_to_eat> "
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

void	throw_thread_create(t_mgc mgc)
{
	perror("thread create failed");
	mgc_free(mgc);
	exit(EXIT_FAILURE);
}

void	try_alloc(t_mgc mgc, void *ptr)
{
	if (!ptr)
	{
		perror("memory allocation failed");
		mgc_free(mgc);
		exit(EXIT_FAILURE);
	}
}
