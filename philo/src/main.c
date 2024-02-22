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

int	is_all_numbers(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (!is_number(args[i]))
			return (0);
	}
	return (1);
}

int	join_threads(t_program *program, pthread_t threads[],
	pthread_t monitor_thread)
{
	if (program->current_philos != program->number_of_philosophers)
	{
		while (--program->current_philos >= 0)
			pthread_join(threads[program->current_philos], NULL);
		pthread_join(monitor_thread, NULL);
		return (1);
	}
	while (--program->current_philos >= 0)
		pthread_join(threads[program->current_philos], NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}

// returns 1 if anything fails
// returns 0 if all worked
int	spawn_philos(t_program *program)
{
	pthread_t	threads[PTHREAD_THREADS_MAX - 1];
	pthread_t	monitor_thread;
	long		time;

	monitor_thread = 0;
	program->current_philos = 0;
	program->philos = malloc(sizeof(t_philo) * program->number_of_philosophers);
	if (!program->philos)
		return (1);
	time = get_current_time();
	while (program->current_philos < program->number_of_philosophers
		&& program->current_philos < PTHREAD_THREADS_MAX - 1)
	{
		program->philos[program->current_philos].id = program->current_philos;
		program->philos[program->current_philos].thread_create = time;
		program->philos[program->current_philos].program = program;
		if (pthread_create(&threads[program->current_philos],
				NULL, &philosopher, &program->philos[program->current_philos])
			!= 0)
			break ;
		program->current_philos++;
	}
	pthread_create(&monitor_thread, NULL, &monitor, program);
	return (join_threads(program, threads, monitor_thread));
}

int	main(int argc, char **argv)
{
	t_program	*program;
	int			i;
	int			return_value;

	i = -1;
	if (input_invalid(argc, argv))
		return (1);
	program = malloc(sizeof(t_program));
	if (setup(argv, program))
		return (1);
	while (++i < program->number_of_philosophers)
		pthread_mutex_init(&program->forks[i], NULL);
	if (argc == 6)
		program->must_eat_count = ft_atoi(argv[5]);
	else
		program->must_eat_count = -1;
	return_value = spawn_philos(program);
	destroy(program, i);
	return (return_value);
}
