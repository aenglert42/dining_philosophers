#include "philo.h"

static char	*static_forward_log_message(int statuscode)
{
	if (statuscode == FORK)
		return ("has taken a fork");
	else if (statuscode == EAT)
		return ("is eating");
	else if (statuscode == SLEEP)
		return ("is sleeping");
	else if (statuscode == THINK)
		return ("is thinking");
	else if (statuscode == DEAD)
		return ("died");
	else if (statuscode == DROP)
		return ("droped the forks");
	else
		return ("Error");
}

long	log_status(int statuscode, t_philo *philo)
{
	long	timestamp_in_ms;
	char	*message;

	pthread_mutex_lock(&philo->data->print_lock);
	timestamp_in_ms = get_timestamp(philo->data->starttime_program);
	message = static_forward_log_message(statuscode);
	if (shouldstop(philo->data) == false || statuscode == DEAD)
		printf("%ld\t%d %s\n", timestamp_in_ms, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (timestamp_in_ms);
}
