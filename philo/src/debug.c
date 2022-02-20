/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:10:26 by englot            #+#    #+#             */
/*   Updated: 2022/02/07 22:07:37 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_result(t_data *data)
{
	int		i;
	long	end;

	i = 0;
	end = data->endtime_program;
	printf("<<<<<<<<<<<<<<<<<<<<<<<<RESULT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	while (data->philos[i] != NULL)
	{
		printf("Philosopher %d ate %d meal", data->philos[i]->id,
			data->philos[i]->mealcount);
		if (data->philos[i]->mealcount != 1)
			printf("s");
		if (data->philos[i]->isdead == true)
			printf(" and died. ");
		else
			printf(" and is alive. ");
		printf("Lifetime: %ld/%ld\n", end, data->philos[i]->deathtime);
		i++;
	}
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

void	print_data(t_data *data)
{
	printf("<<<<<<<<<<<<<<<<<<<<<<<<DEBUGGER>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Number of philosophers: %d\n", data->num_of_philos);
	printf("Time to die: %ld\n", data->time_to_die);
	printf("Time to eat: %ld\n", data->time_to_eat);
	printf("Time to sleep: %ld\n", data->time_to_sleep);
	if (data->islimited)
		printf("Count: %d\n", data->number_of_minmeals);
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}
