/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/02/06 15:02:52 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <unistd.h>

void	sleep_philo(t_philo *philo)
{
	printf("%s%.2fms %d is sleeping%s\n", COLOR_BLUE,
		get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
	ft_usleep(philo->program->time_to_sleep, philo->last_eat, philo->program);
}

void	eat(t_philo *philo)
{
	printf("%s%.2fms %d is eating%s\n", COLOR_MAGENTA,
		get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
	philo->last_eat = get_current_time();
	ft_usleep(philo->program->time_to_eat, philo->last_eat, philo->program);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->id + 1]);
}

void	think(t_philo *philo)
{
	printf("%s%.2fms %d is thinking%s\n", COLOR_CYAN,
		get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->program->forks[philo->id]);
		printf("%s%.2fms %d has taken left fork%s\n", COLOR_GREEN,
			get_converted_time(philo->thread_create),
			philo->id, COLOR_RESET);
		if (philo->id == philo->program->number_of_philosophers - 1)
		{
			philo->program->fork_count[0]++;
			pthread_mutex_lock(&philo->program->forks[0]);
		}
		else
		{
			philo->program->fork_count[philo->id + 1]++;
			pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
		}
		printf("%s%.2fms %d has taken right fork%s\n", COLOR_GREEN,
			get_converted_time(philo->thread_create),
			philo->id, COLOR_RESET);
	}
	else
	{
		if (philo->id == philo->program->number_of_philosophers - 1)
		{
			philo->program->fork_count[0]++;
			pthread_mutex_lock(&philo->program->forks[0]);
		}
		else
		{
			philo->program->fork_count[philo->id + 1]++;
			pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
		}
		printf("%s%.2fms %d has taken right fork%s\n", COLOR_GREEN,
			get_converted_time(philo->thread_create),
			philo->id, COLOR_RESET);
		pthread_mutex_lock(&philo->program->forks[philo->id]);
		printf("%s%.2fms %d has taken left fork%s\n", COLOR_GREEN,
			get_converted_time(philo->thread_create),
			philo->id, COLOR_RESET);
	}
}

void	*philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->eat_count = 0;
	if (philo->program->number_of_philosophers == 1)
	{
		printf("%s%.2fms %d is thinking%s\n", COLOR_CYAN,
			get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
		ft_usleep(philo->program->time_to_die, philo->last_eat, philo->program);
		printf("%s%.2fms %d died%s\n", COLOR_RED,
					get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
		return (NULL);
	}
	write(2, "z\n", 2);
	while (philo->program->dead == 0)
	{
		think(philo);
		eat(philo);
		if (philo->program->must_eat_count != -1
			&& philo->eat_count >= philo->program->must_eat_count)
			{
				printf("%s%.2fms %d has eaten enough%s\n", COLOR_YELLOW,
					get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
				return (NULL);
			}
		if (get_current_time() - philo->last_eat >= philo->program->time_to_die)
		{
			ft_usleep(philo->program->time_to_die, philo->last_eat, philo->program);
			printf("%s%.2fms %d died%s\n", COLOR_RED,
				get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
			philo->program->dead = 1;
			return (NULL);
		}
		sleep_philo(philo);
	}
	return (NULL);
}
