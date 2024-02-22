/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intra <intra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/02/22 10:56:45 by intra            ###   ########.fr       */
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
	if (philo->program->dead == 1)
		return ;
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

void	think(t_philo *philo)
{
	if (philo->program->dead == 1)
		return ;
	print_action(philo, "is thinking", COLOR_CYAN);
	if (philo->id % 2 == 0)
	{
		if (philo->program->dead == 1)
			return ;
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		if (philo->program->dead == 1)
			return ;
		take_right_fork(philo);
		take_left_fork(philo);
	}
}

void	philo_loop(t_philo *philo)
{
	while (philo->program->dead == 0)
	{
		think(philo);
		eat(philo);
		if (philo->program->must_eat_count != -1
			&& philo->eat_count >= philo->program->must_eat_count)
			break ;
		sleep_philo(philo);
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
		print_action(philo, "is thinking", COLOR_CYAN);
		ft_usleep(philo->program->time_to_die, philo->program);
		print_action(philo, "died", COLOR_RED);
		unlock_after_end(philo);
		return (NULL);
	}
	philo_loop(philo);
	unlock_after_end(philo);
	return (NULL);
}
