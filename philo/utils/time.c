/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intra <intra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:52:55 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/22 10:45:22 by intra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// returns current time in microseconds
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
	return ((float)(get_current_time() - start));
}
