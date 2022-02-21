#include "philo.h"

static int	static_join_threads(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i]->thread, NULL))
			return (print_error(THREADJ));
		i++;
	}
	if (pthread_join(data->deathcontrol, NULL))
		return (print_error(THREADJ));
	return (EXIT_SUCCESS);
}

static void	static_initialize_philos(t_data *data)
{
	int	i;

	i = 0;
	while (data->philos[i] != NULL)
	{
		data->philos[i]->data = data;
		data->philos[i]->id = i + 1;
		data->philos[i]->thread = 0;
		data->philos[i]->mealcount = 0;
		data->philos[i]->deathtime = data->time_to_die;
		data->philos[i]->starttime_activity = 0;
		data->philos[i]->endtime_activity = 0;
		i++;
	}
}

int	static_initialize_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->philos[i]->philo_lock, NULL))
			return (print_error(MUTEX));
		if (pthread_mutex_init(data->forks[i], NULL))
			return (print_error(MUTEX));
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (print_error(MUTEX));
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (print_error(MUTEX));
	return (EXIT_SUCCESS);
}

static int	static_initialize(t_data *data)
{
	data->shouldstop = false;
	static_initialize_philos(data);
	if (static_initialize_mutex(data))
		return (EXIT_FAILURE);
	data->starttime_program = get_current_time();
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (parse_input(&data, argc, argv))
		return (EXIT_FAILURE);
	if (DEBUGGING)
		print_data(&data);
	if (allocate_memory(&data))
		return (free_data(&data));
	if (static_initialize(&data))
		return (free_data(&data));
	if (create_threads(&data))
		return (free_data(&data));
	if (static_join_threads(&data))
		return (free_data(&data));
	if (DEBUGGING)
		print_result(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
