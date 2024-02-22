/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:52:55 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/22 12:08:06 by jkauker          ###   ########.fr       */
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

int	ft_usleep(int time_in_ms, t_program *program)
{
	long	start;

	start = get_current_time();
	program = 0;
	while (get_current_time() - start < time_in_ms)
	{
		// if (program->dead == 1)
		// 	return (0);
		usleep(250);
	}
	return (1);
}

float	get_converted_time(long start)
{
	return ((float)(get_current_time() - start));
}
