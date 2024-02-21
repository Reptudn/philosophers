/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:52:55 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/21 10:00:26 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// returns current time in microseconds
long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

int	ft_usleep(int time_in_ms, t_program *program)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time_in_ms)
	{
		if (program->dead == 1)
			return (0);
		usleep(250);
	}
	return (1);
}

float	get_converted_time(long start)
{
	return ((float)(get_current_time() - start) / 1000);
}
