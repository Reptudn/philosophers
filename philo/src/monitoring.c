/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:53:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/01/22 10:36:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	everyone_ate(t_program *program)
{
	int	i;

	i = 0;
	if (program->must_eat_count == -1)
		return (0);
	while (i < program->current_philos)
	{
		if (program->philos[i].eat_count < program->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *args)
{
	int			i;
	t_program	*program;
	long		time;

	program = (t_program *)args;
	while (program->dead == 0)
	{
		if (everyone_ate(program))
		{
			program->dead = 1;
			break ;
		}
		i = 0;
		while (i < program->current_philos)
		{
			time = get_current_time();
			if (time - program->philos[i].last_eat
				>= program->philos[i].program->time_to_die)
			{
				printf("%ld\n", time - program->philos[i].last_eat);
				printf("%d\n", program->philos[i].program->time_to_die);
				program->dead = 1;
				pthread_mutex_lock(program->print_mutex);
				printf("%s%.2fms %d died%s\n", COLOR_RED,
					get_converted_time(program->philos[i].thread_create),
					program->philos[i].id + 1, COLOR_RESET);
				pthread_mutex_lock(program->print_mutex);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
