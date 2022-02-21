/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_threads_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:16:00 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:16:01 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	static_pickupforks_helper(t_philo *philo, int fork1, int fork2)
{
	pthread_mutex_lock(philo->data->forks[fork1]);
	if (shouldstop(philo->data))
	{
		pthread_mutex_unlock(philo->data->forks[fork1]);
		return (EXIT_FAILURE);
	}
	log_status(FORK, philo);
	if (philo->data->num_of_philos != 1)
		pthread_mutex_lock(philo->data->forks[fork2]);
	else
	{
		pthread_mutex_unlock(philo->data->forks[fork1]);
		return (EXIT_FAILURE);
	}
	if (shouldstop(philo->data))
	{
		pthread_mutex_unlock(philo->data->forks[fork1]);
		pthread_mutex_unlock(philo->data->forks[fork2]);
		return (EXIT_FAILURE);
	}
	log_status(FORK, philo);
	return (EXIT_SUCCESS);
}

static int	static_pickupforks(t_philo *philo)
{
	int	fork1;
	int	fork2;

	fork1 = (philo->id) % philo->data->num_of_philos;
	fork2 = philo->id - 1;
	if (philo->id % 2)
	{
		fork1 = philo->id - 1;
		fork2 = (philo->id) % philo->data->num_of_philos;
	}
	if (static_pickupforks_helper(philo, fork1, fork2))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	static_think(t_philo *philo)
{
	if (shouldstop(philo->data))
		return (EXIT_FAILURE);
	log_status(THINK, philo);
	return (EXIT_SUCCESS);
}

static void	*static_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		static_think(philo);
	while (!(philo->id % 2) && is_busy(philo, philo->data->time_to_eat / 2 + 9))
	{
		if (shouldstop(philo->data))
			break ;
		usleep(WAITTIME);
	}
	while (shouldstop(philo->data) == false)
	{
		if (static_pickupforks(philo))
			break ;
		if (philo_eat(philo))
		{
			dropforks(philo);
			break ;
		}
		if (philo_sleep(philo))
			break ;
		static_think(philo);
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				static_philo_routine, data->philos[i]))
			return (print_error(THREADC));
		i++;
	}
	if (pthread_create(&data->deathcontrol, NULL, control_routine, data))
		return (print_error(THREADC));
	return (EXIT_SUCCESS);
}
