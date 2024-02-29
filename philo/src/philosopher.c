/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intra <intra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/02/29 10:42:37 by intra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping", COLOR_BLUE);
	ft_usleep(philo->program->time_to_sleep);
}

void	eat(t_philo *philo)
{
	print_action(philo, "is eating", COLOR_MAGENTA);
	ft_usleep(philo->program->time_to_eat);
	philo->last_eat = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->id + 1]);
}

void	think(t_philo *philo)
{
	print_action(philo, "is thinking", COLOR_CYAN);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->program->forks[philo->id]);
	print_action(philo, "has taken a fork", COLOR_GREEN);
		if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->program->forks[0]);
		else
			pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
		print_action(philo, "has taken a fork", COLOR_GREEN);
	}
	else
	{
		if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->program->forks[0]);
		else
			pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
		print_action(philo, "has taken a fork", COLOR_GREEN);
		pthread_mutex_lock(&philo->program->forks[philo->id]);
	print_action(philo, "has taken a fork", COLOR_GREEN);
	}
}

void	philo_loop(t_philo *philo)
{
	while (is_dead(philo->program) == 0)
	{
		think(philo);
		eat(philo);
		if (philo->program->must_eat_count != -1
			&& philo->eat_count >= philo->program->must_eat_count)
			break ;
		sleep_philo(philo);
	}
}

int	get_eat_count(t_philo *philo)
{
	int	eat_count;

	eat_count = philo->eat_count;
	return (eat_count);
}

void	*philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->eat_count = 0;
	if (philo->program->number_of_philosophers % 2 == 1)
	{
		if (philo->program->number_of_philosophers >= 100)
			ft_usleep(philo->id % 50);
		else
			ft_usleep(philo->id % 20);
	}
	if (philo->program->number_of_philosophers == 1)
	{
		print_action(philo, "is thinking", COLOR_CYAN);
		ft_usleep(philo->program->time_to_die);
		print_action(philo, "died", COLOR_RED);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->program->time_to_eat);
	philo_loop(philo);
	return (NULL);
}
