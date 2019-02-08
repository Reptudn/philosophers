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

	program = (t_program *)args;
	while (program->dead == 0)
	{
		if (everyone_ate(program))
			break ;
		i = 0;
		while (i < program->current_philos)
		{
			if (program->philos[i].last_eat + program->time_to_die
				< get_current_time())
			{
				program->dead = 1;
				printf("%s%.2fms %d died%s\n", COLOR_RED,
					get_converted_time(program->philos[i].thread_create),
					program->philos[i].id, COLOR_RESET);
				return (NULL);
			}
			printf("pog\n");
			i++;
		}
		break ;
	}
	return (NULL);
}
