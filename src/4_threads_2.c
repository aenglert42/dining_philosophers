/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_threads_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:16:03 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:16:04 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_busy(t_philo *philo, long endtime_activity)
{
	long	current_time;

	current_time = get_timestamp(philo->data->starttime_program);
	if (current_time >= endtime_activity)
		return (false);
	return (true);
}

static int	static_doactivity(t_philo *philo)
{
	while (is_busy(philo, philo->endtime_activity))
	{
		if (shouldstop(philo->data))
			return (EXIT_FAILURE);
		usleep(WAITTIME);
	}
	return (EXIT_SUCCESS);
}

void	dropforks(t_philo *philo)
{
	pthread_mutex_unlock(philo->data->forks[philo->id - 1]);
	pthread_mutex_unlock(philo->data->forks[(philo->id)
		% philo->data->num_of_philos]);
	if (DEBUGGING)
		log_status(DROP, philo);
}

int	philo_eat(t_philo *philo)
{
	if (shouldstop(philo->data))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&philo->philo_lock);
	philo->starttime_activity = log_status(EAT, philo);
	philo->deathtime = philo->starttime_activity + philo->data->time_to_die;
	philo->endtime_activity = philo->starttime_activity
		+ philo->data->time_to_eat;
	pthread_mutex_unlock(&philo->philo_lock);
	if (static_doactivity(philo))
		return (EXIT_FAILURE);
	if (shouldstop(philo->data))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&philo->philo_lock);
	philo->mealcount++;
	pthread_mutex_unlock(&philo->philo_lock);
	if (shouldstop(philo->data))
		return (EXIT_FAILURE);
	dropforks(philo);
	return (EXIT_SUCCESS);
}

int	philo_sleep(t_philo *philo)
{
	if (shouldstop(philo->data))
		return (EXIT_FAILURE);
	philo->starttime_activity = log_status(SLEEP, philo);
	philo->endtime_activity = philo->starttime_activity
		+ philo->data->time_to_sleep;
	return (static_doactivity(philo));
}
