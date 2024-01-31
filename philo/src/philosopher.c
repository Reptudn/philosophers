/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/01/31 13:25:54 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

void	sleep_philo(t_philo *philo)
{
	printf("%s%.2fms %d is sleeping%s\n", COLOR_BLUE,
		get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
	ft_usleep(philo->program->time_to_sleep);
}

void	eat(t_philo *philo)
{
	printf("%s%.2fms %d is eating%s\n", COLOR_MAGENTA,
		get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
	philo->last_eat = get_current_time();
	ft_usleep(philo->program->time_to_eat);
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

	// left fork
	pthread_mutex_lock(&philo->program->forks[philo->id]);
	printf("%s%.2fms %d has taken left fork%s\n", COLOR_GREEN,
		get_converted_time(philo->thread_create),
		philo->id, COLOR_RESET);

	// right fork
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->program->forks[0]);
	else
		pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
	printf("%s%.2fms %d has taken right fork%s\n", COLOR_GREEN,
		get_converted_time(philo->thread_create),
		philo->id, COLOR_RESET);
}

// log format "timestamp_in_ms X died"
void	*philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->eat_count = 0;
	if (philo->program->must_eat_count == -1)
	{
		while (philo->eat_count < philo->program->must_eat_count
			&& philo->program->dead == 0)
		{
			think(philo);
			eat(philo);
			sleep_philo(philo);
		}
	}
	else
	{
		while (philo->program->dead == 0)
		{
			think(philo);
			eat(philo);
			if (get_current_time() - philo->last_eat >= philo->program->time_to_die)
			{
				philo->program->dead = 1;
				break ;
			}
			sleep_philo(philo);
		}
	}
	printf("%s%.2fms %d died%s\n", COLOR_RED,
		get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
	return (NULL);
}
