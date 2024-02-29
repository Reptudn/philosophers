/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/02/29 16:13:58 by jkauker          ###   ########.fr       */
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
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->id + 1]);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
}

void	think(t_philo *philo)
{
	print_action(philo, "is thinking", COLOR_CYAN);
	if (philo->id % 2 == 0)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
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

void	*philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_init(&philo->last_eat_mutex, NULL);
	pthread_mutex_init(&philo->eat_count_mutex, NULL);
	if (philo->program->number_of_philosophers % 2 == 1)
	{
		if (philo->program->number_of_philosophers >= 100)
			ft_usleep(philo->id % 50);
		else
			ft_usleep(philo->id % 20);
	}
	// if (philo->program->number_of_philosophers == 1)
	// {
	// 	print_action(philo, "is thinking", COLOR_CYAN);
	// 	ft_usleep(philo->program->time_to_die);
	// 	print_action(philo, "died", COLOR_RED);
	// 	return (NULL);
	// }
	if (philo->id % 2 == 0)
		ft_usleep(philo->program->time_to_eat);
	philo_loop(philo);
	pthread_mutex_destroy(&philo->last_eat_mutex);
	pthread_mutex_destroy(&philo->eat_count_mutex);
	return (NULL);
}
