/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:41:17 by englot            #+#    #+#             */
/*   Updated: 2022/02/14 09:30:11 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define WAITTIME 100
# define INFINITE -5
# define ATOIERROR -1

typedef enum e_statuscode
{
	FORK = 1,
	EAT = 2,
	SLEEP = 3,
	THINK = 4,
	DEAD = 5,
	DROP = 6,
}	t_statuscode;

typedef enum e_errorcode
{
	ARGMIN = 0,
	ARGMAX = 1,
	NONNUM = 2,
	MININT = 3,
	MAXINT = 4,
	MALLOC = 5,
	THREADC = 6,
	THREADJ = 7,
	MUTEX = 8,
}	t_errorcode;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	bool			isdead;
	pthread_t		thread;
	pthread_mutex_t	philo_lock;
	int				mealcount;
	long			deathtime;
	long			starttime_activity;
	long			endtime_activity;
}	t_philo;

typedef struct s_data
{
	pthread_t		deathcontrol;
	int				num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_minmeals;
	bool			islimited;
	t_philo			**philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	long			starttime_program;
	long			endtime_program;
	bool			shouldstop;
}	t_data;

//parse
int		parse_input(t_data *data, int argc, char **argv);

//allocate
int		allocate_memory(t_data *data);

//thread
int		create_threads(t_data *data);
void	dropforks(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
bool	shouldstop(t_data *data);
bool	shoulddie(t_philo *philo);
void	*control_routine(void *arg);
bool	is_busy(t_philo *philo, long endtime_activity);

//log
long	log_status(int statuscode, t_philo *philo);

//time
long	get_current_time(void);
long	get_timestamp(long start_time);

//free
int		free_data(t_data *data);

//utils
int		philo_atoi(const char *str);
size_t	ft_strlen(const char *str);
bool	is_positive_number(char *str);

//error
int		print_error(int errorcode);

//debug
void	print_data(t_data *data);
void	print_result(t_data *data);

#endif