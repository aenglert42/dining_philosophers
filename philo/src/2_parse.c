/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:09:42 by englot            #+#    #+#             */
/*   Updated: 2022/02/07 14:46:57 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	static_convert_args(t_data *data, char **argv)
{
	data->num_of_philos = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	data->islimited = false;
	if (argv[5] != NULL)
	{
		data->number_of_minmeals = philo_atoi(argv[5]);
		data->islimited = true;
	}
	else
		data->number_of_minmeals = INFINITE;
	if ((data->num_of_philos < 0
			|| data->time_to_die < 0
			|| data->time_to_eat < 0
			|| data->time_to_sleep < 0)
		|| (data->islimited && data->number_of_minmeals == ATOIERROR))
		return (print_error(MAXINT));
	if (data->num_of_philos < 1)
		return (print_error(MININT));
	return (EXIT_SUCCESS);
}

static int	static_check_valid_int(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (!is_positive_number(argv[i]))
			return (print_error(NONNUM));
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	static_check_number_of_arguments(int argc)
{
	if (argc < 5)
		return (print_error(ARGMIN));
	else if (argc > 6)
		return (print_error(ARGMAX));
	return (EXIT_SUCCESS);
}

int	parse_input(t_data *data, int argc, char **argv)
{
	if (static_check_number_of_arguments(argc)
		|| static_check_valid_int(argv)
		|| static_convert_args(data, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
