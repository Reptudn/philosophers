/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:46:02 by jkauker           #+#    #+#             */
/*   Updated: 2024/01/22 10:23:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	spawn_philos(t_program *program)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < program->number_of_philosophers)
	{
		
	}
	return (0);
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
		program.time_to_sleep = ft_atoi(argv[5]);
	else
		program.time_to_sleep = -1;
	if (!spawn_philos(&program))
	{
		// free memory
		return (1);
	}
	while (!program.dead)
	{
		continue ;
	}
	return (0);
}
