/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:39:31 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/05 15:39:32 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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