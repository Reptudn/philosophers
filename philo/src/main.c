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

// returns 0 if anything fails
// returns 1 if all worked
int	spawn_philos(t_program *program)
{
	pthread_t	threads[PTHREAD_THREADS_MAX - 1];
	pthread_t	monitor_thread;
	long		time;

	monitor_thread = 0;
	program->current_philos = 0;
	program->philos = malloc(sizeof(t_philo) * program->number_of_philosophers);
	if (!program->philos)
		return (0);
	time = get_current_time();
	while (program->current_philos < program->number_of_philosophers
		&& program->current_philos < PTHREAD_THREADS_MAX - 1)
	{
		program->philos[program->current_philos].id = program->current_philos;
		program->philos[program->current_philos].thread_create = time;
		program->philos[program->current_philos].program = program;
		if (pthread_create(&threads[program->current_philos],
				NULL, &philosopher, &program->philos[program->current_philos]) != 0)
			break ;
		program->current_philos++;
	}
	pthread_create(&monitor_thread, NULL, &monitor, program);
	if (program->current_philos != program->number_of_philosophers)
	{
		while (--program->current_philos >= 0)
			pthread_join(threads[program->current_philos], NULL);
		pthread_join(monitor_thread, NULL);
		return (0);
	}
	while (--program->current_philos >= 0)
		pthread_join(threads[program->current_philos], NULL);
	pthread_join(monitor_thread, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	*program;
	int			i;

	i = -1;
	if (argc < 5 || argc > 6 || !is_all_numbers(argv))
	{
		printf("%sUsage: ./philo number_of_philosophers time_to_die \
		time_to_eat time_to_sleep  \
		[number_of_times_each_philosopher_must_eat%s\n",
			COLOR_RED, COLOR_RESET);
		return (1);
	}
	program = malloc(sizeof(t_program));
	if (!program)
		return (1);
	program->number_of_philosophers = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	program->forks = malloc(sizeof(pthread_mutex_t)
			* program->number_of_philosophers);
	if (!program->forks)
		return (1);
	program->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!program->print_mutex)
		return (1);
	while (++i < program->number_of_philosophers)
		pthread_mutex_init(&program->forks[i], NULL);
	if (argc == 6)
		program->must_eat_count = ft_atoi(argv[5]);
	else
		program->must_eat_count = -1;
	program->dead = 0;
	spawn_philos(program);
	while (--i >= 0)
		pthread_mutex_destroy(&program->forks[i]);
	pthread_mutex_destroy(program->print_mutex);
	free(program);
	printf("End of program\n");
	return (0);
}
