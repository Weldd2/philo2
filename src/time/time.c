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
