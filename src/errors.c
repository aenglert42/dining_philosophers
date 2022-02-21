/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:16:20 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:16:21 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*static_forward_errormessage(int errorcode)
{
	if (errorcode == ARGMIN)
		return ("Error: missing arguments\n");
	else if (errorcode == ARGMAX)
		return ("Error: too many arguments\n");
	else if (errorcode == NONNUM)
		return ("Error: only numeric characters allowed\n");
	else if (errorcode == MININT)
		return ("Error: at least one philosopher required\n");
	else if (errorcode == MAXINT)
		return ("Error: number greater INT_MAX\n");
	else if (errorcode == MALLOC)
		return ("Error: malloc failed\n");
	else if (errorcode == THREADC)
		return ("Error: could not create thread\n");
	else if (errorcode == THREADJ)
		return ("Error: could not join thread\n");
	else if (errorcode == MUTEX)
		return ("Error: mutex_init failed\n");
	else
		return ("Error\n");
}

int	print_error(int errorcode)
{
	char	*message;

	message = static_forward_errormessage(errorcode);
	write(STDERR_FILENO, message, ft_strlen(message));
	return (EXIT_FAILURE);
}
