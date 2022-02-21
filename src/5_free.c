/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:16:11 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:16:12 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	static_free_forks(t_data *data)
{
	int	i;

	i = 0;
	while (data->forks[i] != NULL)
	{
		pthread_mutex_destroy(data->forks[i]);
		free(data->forks[i]);
		data->forks[i] = NULL;
		i++;
	}
	free(data->forks[i]);
	data->forks[i] = NULL;
	free(data->forks);
	data->forks = NULL;
}

static void	static_free_philos(t_data *data)
{
	int	i;

	i = 0;
	while (data->philos[i] != NULL)
	{
		pthread_mutex_destroy(&data->philos[i]->philo_lock);
		free(data->philos[i]);
		data->philos[i] = NULL;
		i++;
	}
	free(data->philos[i]);
	data->philos[i] = NULL;
	free(data->philos);
	data->philos = NULL;
}

int	free_data(t_data *data)
{
	if (data->philos != NULL)
		static_free_philos(data);
	if (data->forks != NULL)
		static_free_forks(data);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	return (EXIT_FAILURE);
}
