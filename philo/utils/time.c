/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intra <intra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:52:55 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/23 13:49:35 by intra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// returns current time in ms
long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(int time_in_ms)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time_in_ms)
	{
		usleep(250);
	}
	return (1);
}

float	get_converted_time(long start)
{
	return ((float)(get_current_time() - start));
}

int	make_dead_mutex(t_program *program)
{
	program->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!program->dead_mutex)
	{
		free(program->forks);
		free(program->print_mutex);
		free(program);
		return (1);
	}
	pthread_mutex_init(program->dead_mutex, NULL);
	return (0);
}
