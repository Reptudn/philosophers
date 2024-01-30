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
#include <sys/_pthread/_pthread_t.h>

// returns 0 if anything fails
// returns 1 fi all worked
int	spawn_philos(t_program *program)
{
	pthread_t	threads[PTHREAD_THREADS_MAX];

	program->current_philos = 0;
	program->philos = malloc(sizeof(t_philo) * program->number_of_philosophers);
	if (!program->philos)
		return (0);
	while (program->current_philos < program->number_of_philosophers
		&& program->current_philos < PTHREAD_THREADS_MAX)
	{
		if (pthread_create(&threads[program->current_philos],
				NULL, &philosopher, NULL) != 0)
			break ;
		program->philos[program->current_philos].id
			= threads[program->current_philos];
		++program->current_philos;
	}
	if (program->current_philos != program->number_of_philosophers)
	{
		while (--program->current_philos >= 0)
			pthread_join(threads[program->current_philos], NULL);
		return (0);
	}
	while (--program->current_philos >= 0)
		pthread_join(threads[program->current_philos], NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
	{
		printf("%sUsage: ./philo number_of_philosophers time_to_die \
		time_to_eat time_to_sleep  \
		[number_of_times_each_philosopher_must_eat%s\n",
			COLOR_RED, COLOR_RESET);
		return (1);
	}
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
		return (1);
	return (0);
}
