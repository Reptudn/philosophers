/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:46:18 by intra             #+#    #+#             */
/*   Updated: 2024/02/22 12:13:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philo, char *action, char *color)
{
	if (philo->program->dead == 1)
		return ;
	pthread_mutex_lock(philo->program->print_mutex);
	if (philo->program->dead == 1)
	{
		pthread_mutex_unlock(philo->program->print_mutex);
		return ;
	}
	printf("%s%.0f %d %s%s\n", color,
		get_converted_time(philo->thread_create),
		philo->id + 1, action, COLOR_RESET);
	pthread_mutex_unlock(philo->program->print_mutex);
}

void	take_left_fork(t_philo *philo)
{
	if (philo->program->dead == 1)
		return ;
	pthread_mutex_lock(&philo->program->forks[philo->id]);
	print_action(philo, "has taken a fork", COLOR_GREEN);
}

void	take_right_fork(t_philo *philo)
{
	if (philo->program->dead == 1)
		return ;
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->program->forks[0]);
	else
		pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
	print_action(philo, "has taken a fork", COLOR_GREEN);
}

int	setup(char **argv, t_program *program)
{
	if (!program)
		return (1);
	program->number_of_philosophers = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	program->dead = 0;
	program->forks = malloc(sizeof(pthread_mutex_t)
			* program->number_of_philosophers);
	if (!program->forks)
	{
		free(program);
		return (1);
	}
	program->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!program->print_mutex)
	{
		free(program->forks);
		free(program);
		return (1);
	}
	pthread_mutex_init(program->print_mutex, NULL);
	return (0);
}

void	destroy(t_program *program, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&program->forks[i]);
	pthread_mutex_destroy(program->print_mutex);
	free(program->forks);
	free(program->print_mutex);
	free(program->philos);
	free(program);
}
