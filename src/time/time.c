/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:47:13 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/05 15:47:14 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timestamp	get_timestamp(void)
{
	struct timeval		tv;
	static t_timestamp	base = 0;

	gettimeofday(&tv, NULL);
	if (base == 0)
		base = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - base);
}
