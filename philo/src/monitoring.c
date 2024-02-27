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

int	everyone_ate(t_program *program)
{
	int	i;

	i = 0;
	if (program->must_eat_count == -1)
		return (0);
	while (i < program->current_philos)
	{
		if (program->philos[i].eat_count < program->must_eat_count)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	set_dead(t_program *program)
{
	pthread_mutex_lock(program->dead_mutex);
	program->dead = 1;
	pthread_mutex_unlock(program->dead_mutex);
}

int	is_dead(t_program *program)
{
	int	dead;

	pthread_mutex_lock(program->dead_mutex);
	dead = program->dead;
	pthread_mutex_unlock(program->dead_mutex);
	return (dead);
}

void	*monitor(void *args)
{
	int			i;
	t_program	*program;
	long		time;

	program = (t_program *)args;
	while (program->dead == 0 && program->number_of_philosophers > 1)
	{
		if (everyone_ate(program))
			break ;
		i = -1;
		while (++i < program->current_philos)
		{
			time = get_current_time();
			if (time - program->philos[i].last_eat
				>= program->philos[i].program->time_to_die)
			{
				print_action(&program->philos[i], "died", COLOR_RED);
				set_dead(program);
				return (NULL);
			}
		}
	}
	set_dead(program);
	return (NULL);
}
