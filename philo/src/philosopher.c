/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/02/19 15:10:49 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	sleep_philo(t_philo *philo)
{
	if (philo->program->dead == 1)
		return ;
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

void	unlock_after_end(t_philo *philo)
{
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->id + 1]);
	printf("%s%.2fms %d put all forks back%s\n", COLOR_YELLOW, get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
}

void	think(t_philo *philo)
{
	if (philo->program->dead == 1)
		return ;
	printf("%s%.2fms %d is thinking%s\n", COLOR_CYAN,
		get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
	if (philo->id % 2 == 0)
	{
		if (philo->program->dead == 1)
			return ;
		pthread_mutex_lock(&philo->program->forks[philo->id]);
		printf("%s%.2fms %d has taken left fork%s\n", COLOR_GREEN,
			get_converted_time(philo->thread_create),
			philo->id, COLOR_RESET);
		if (philo->id == philo->program->number_of_philosophers - 1)
			pthread_mutex_lock(&philo->program->forks[0]);
		else
			pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
		printf("%s%.2fms %d has taken right fork%s\n", COLOR_GREEN,
			get_converted_time(philo->thread_create),
			philo->id, COLOR_RESET);
	}
	else
	{
		if (philo->program->dead == 1)
			return ;
		if (philo->id == philo->program->number_of_philosophers - 1)
			pthread_mutex_lock(&philo->program->forks[0]);
		else
			pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
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
	philo->last_eat = __INT_MAX__;
	if (philo->program->number_of_philosophers == 1)
	{
		printf("%s%.2fms %d is thinking%s\n", COLOR_CYAN,
			get_converted_time(philo->thread_create), philo->id, COLOR_RESET);
		ft_usleep(philo->program->time_to_die, philo->last_eat,
			philo->program);
		printf("%s%.2fms %d died%s\n", COLOR_RED,
			get_converted_time(philo->thread_create), philo->id,
			COLOR_RESET);
		return (NULL);
	}
	while (philo->program->dead == 0)
	{
		think(philo);
		if (philo->program->dead == 1)
			break ;
		eat(philo);
		if (philo->program->dead == 1)
			break ;
		if (philo->program->must_eat_count != -1
			&& philo->eat_count >= philo->program->must_eat_count)
		{
			printf("%s%.2fms %d has eaten enough%s\n", COLOR_YELLOW,
				get_converted_time(philo->thread_create), philo->id,
				COLOR_RESET);
			break ;
		}
		if (philo->program->dead == 1)
			break ;
		sleep_philo(philo);
		if (philo->program->dead == 1)
			break ;
	}
	unlock_after_end(philo);
	return (NULL);
}
