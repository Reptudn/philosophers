/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:46:02 by jkauker           #+#    #+#             */
/*   Updated: 2024/01/23 09:33:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

int	spawn_philos(t_program *program)
{
	pid_t	pid;

	program->current_philos = -1;
	program->philos = malloc(sizeof(t_philo) * program->number_of_philosophers);
	if (!program->philos)
		return (0);
	while (++program->current_philos < program->number_of_philosophers)
	{
		program->philos[program->current_philos].id = program->current_philos;
		printf("[\t%d\t] Philosopher spawned\n", program->current_philos);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc != 5 || argc != 6)
		return (1);
	program.number_of_philosophers = ft_atoi(argv[1]);
	program.time_to_die = ft_atoi(argv[2]);
	program.time_to_eat = ft_atoi(argv[3]);
	program.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		program.must_eat_count = ft_atoi(argv[5]);
	else
		program.must_eat_count = -1;
	program.dead = 0;
	if (!spawn_philos(&program))
	{
		// free memory
		return (1);
	}
	while (!program.dead)
	{
		continue ;
	}
	// free memory and join threads
	return (0);
}
