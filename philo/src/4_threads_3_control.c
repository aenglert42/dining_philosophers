#include "philo.h"

bool	shoulddie(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	if (get_timestamp(philo->data->starttime_program) > philo->deathtime)
	{
		pthread_mutex_unlock(&philo->philo_lock);
		pthread_mutex_lock(&philo->data->death_lock);
		philo->isdead = true;
		philo->data->shouldstop = true;
		pthread_mutex_unlock(&philo->data->death_lock);
		philo->data->endtime_program = log_status(DEAD, philo);
		return (true);
	}
	else
		pthread_mutex_unlock(&philo->philo_lock);
	return (false);
}

static void	static_check_meals(t_data *data, int i, bool *allmealseaten)
{
	pthread_mutex_lock(&data->philos[i]->philo_lock);
	if (data->philos[i]->mealcount < data->number_of_minmeals)
		*allmealseaten = false;
	pthread_mutex_unlock(&data->philos[i]->philo_lock);
}

static bool	static_allmealseaten(t_data *data, bool allmealseaten)
{
	if (allmealseaten && data->islimited)
	{
		pthread_mutex_lock(&data->death_lock);
		data->shouldstop = true;
		data->endtime_program = get_timestamp(data->starttime_program);
		pthread_mutex_unlock(&data->death_lock);
		return (true);
	}
	return (false);
}

bool	shouldstop(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->shouldstop == true)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (true);
	}
	else
		pthread_mutex_unlock(&data->death_lock);
	return (false);
}

void	*control_routine(void *arg)
{
	t_data	*data;
	int		i;
	bool	allmealseaten;

	data = (t_data *)arg;
	while (1)
	{
		allmealseaten = true;
		i = 0;
		while (i < data->num_of_philos)
		{
			if (shoulddie(data->philos[i]))
				return (NULL);
			static_check_meals(data, i, &allmealseaten);
			i++;
		}
		if (static_allmealseaten(data, allmealseaten))
			return (NULL);
	}
	return (NULL);
}
