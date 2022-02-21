#include "philo.h"

long	get_current_time(void)
{
	long			current_time;
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	current_time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (current_time);
}

long	get_timestamp(long start_time)
{
	long	current_time;
	long	timestamp_in_ms;

	current_time = get_current_time();
	timestamp_in_ms = current_time - start_time;
	return (timestamp_in_ms);
}
