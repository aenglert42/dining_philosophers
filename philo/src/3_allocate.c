#include "philo.h"

static int	static_create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t *) * (data->num_of_philos + 1));
	if (data->forks == NULL)
		return (EXIT_FAILURE);
	while (i < data->num_of_philos)
	{
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (data->forks[i] == NULL)
			return (EXIT_FAILURE);
		i++;
	}
	data->forks[i] = NULL;
	return (EXIT_SUCCESS);
}

int	allocate_memory(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo *) * (data->num_of_philos + 1));
	if (data->philos == NULL)
		return (print_error(MALLOC));
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i] = malloc(sizeof(t_philo));
		if (data->philos[i] == NULL)
			return (print_error(MALLOC));
		i++;
	}
	data->philos[i] = NULL;
	if (static_create_forks(data))
		return (print_error(MALLOC));
	return (EXIT_SUCCESS);
}
