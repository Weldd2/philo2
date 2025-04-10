/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:47:23 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/10 17:59:49 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(char *s)
{
	int	r;

	r = 0;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		r *= 10;
		r += (*s - '0');
		s++;
	}
	if (*s)
		return (-1);
	return (r);
}

bool	check_params(t_params params)
{
	return (
		params.nb_philo > 0
		&& params.time_to_die > 0
		&& params.time_to_eat > 0
		&& params.time_to_sleep > 0
	);
}

t_params	get_params(int argc, char **argv)
{
	t_params	params;

	if (argc != 5 && argc != 6)
		throw_params_count();
	params.nb_philo = is_int(argv[1]);
	params.time_to_die = is_int(argv[2]);
	params.time_to_eat = is_int(argv[3]);
	params.time_to_sleep = is_int(argv[4]);
	params.meal_goal = 0;
	if (!check_params(params))
		throw_params_value();
	if (argc == 6)
	{
		params.meal_goal = is_int(argv[5]);
		if (params.meal_goal <= 0)
			throw_params_value();
	}
	return (params);
}
