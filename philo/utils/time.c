/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:52:55 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/09 09:22:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// returns current time in microseconds
int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

int	ft_usleep(int time_in_ms, int last_eat, t_program *program)
{
	int	start;

	start = get_current_time();
	last_eat++;
	while (get_current_time() - start < time_in_ms)
	{
		if (program->dead == 1)
			return (0);
		// if (get_current_time() - last_eat >= program->time_to_die)
		// {
		// 	if (program->dead == 0)
		// 		program->dead = 1;
		// 	return (0);
		// }
		usleep(250);
	}
	return (1);
}

float	get_converted_time(int start)
{
	return ((float)(get_current_time() - start) / 1000);
}
