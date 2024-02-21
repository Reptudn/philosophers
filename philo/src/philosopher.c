/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/02/21 13:02:43 by jkauker          ###   ########.fr       */
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
	print_action(philo, "is sleeping", COLOR_BLUE);
	ft_usleep(philo->program->time_to_sleep, philo->program);
}

void	eat(t_philo *philo)
{
	print_action(philo, "is eating", COLOR_MAGENTA);
	ft_usleep(philo->program->time_to_eat, philo->program);
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->id + 1]);
	philo->last_eat = get_current_time();
	philo->eat_count++;
}

void	unlock_after_end(t_philo *philo)
{
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->id + 1]);
}

void	think(t_philo *philo)
{
	if (philo->program->dead == 1)
		return ;
	print_action(philo, "is thinking", COLOR_CYAN);
	if (philo->id % 2 == 0)
	{
		if (philo->program->dead == 1)
			return ;
		pthread_mutex_lock(&philo->program->forks[philo->id]);
		print_action(philo, "has taken left fork", COLOR_GREEN);
		if (philo->id == philo->program->number_of_philosophers - 1)
			pthread_mutex_lock(&philo->program->forks[0]);
		else
			pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
		print_action(philo, "has taken right fork", COLOR_GREEN);
	}
	else
	{
		if (philo->program->dead == 1)
			return ;
		if (philo->id == philo->program->number_of_philosophers - 1)
			pthread_mutex_lock(&philo->program->forks[0]);
		else
			pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
		print_action(philo, "has taken right fork", COLOR_GREEN);
		pthread_mutex_lock(&philo->program->forks[philo->id]);
		print_action(philo, "has taken left fork", COLOR_GREEN);
	}
}

void	*philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->eat_count = 0;
	philo->last_eat = get_current_time();
	if (philo->program->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->program->print_mutex);
		printf("%s%.2fms %d is thinking%s\n", COLOR_CYAN,
			get_converted_time(philo->thread_create), philo->id + 1,
			COLOR_RESET);
		pthread_mutex_unlock(philo->program->print_mutex);
		ft_usleep(philo->program->time_to_die, philo->program);
		pthread_mutex_lock(philo->program->print_mutex);
		printf("%s%.2fms %d died%s\n", COLOR_RED,
			get_converted_time(philo->thread_create), philo->id + 1,
			COLOR_RESET);
		pthread_mutex_unlock(philo->program->print_mutex);
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
			print_action(philo, "has eaten enough", COLOR_YELLOW);
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
