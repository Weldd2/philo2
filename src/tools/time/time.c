/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:47:13 by antoinemura       #+#    #+#             */
/*   Updated: 2025/04/10 22:25:00 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timestamp	get_timestamp(void)
{
	static t_timestamp		base = 0;
	static pthread_mutex_t	ts_mutex = PTHREAD_MUTEX_INITIALIZER;
	struct timeval			tv;
	t_timestamp				now;
	t_timestamp				timestamp;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
	pthread_mutex_lock(&ts_mutex);
	if (base == 0)
		base = now;
	timestamp = now - base;
	pthread_mutex_unlock(&ts_mutex);
	return (timestamp);
}

void	ft_msleep(int ms)
{
	t_timestamp	start;
	t_timestamp	target;
	t_timestamp	remaining;

	start = get_timestamp();
	target = start + ms;
	while (get_timestamp() < target)
	{
		remaining = target - get_timestamp();
		if (remaining > 10)
			usleep(500);
		else
			usleep(50);
	}
}
