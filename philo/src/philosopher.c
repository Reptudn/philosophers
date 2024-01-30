/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/01/30 16:52:47 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>

void	sleep_philo(t_philo *philo)
{
	printf("%s%dms %d is sleeping%s\n", COLOR_BLUE, get_current_time() - philo->thread_create, philo->id, COLOR_RESET);
	usleep(philo->program->time_to_sleep);
}

void	eat(t_philo *philo)
{
	printf("%s%dms %d is eating%s\n", COLOR_GREEN, get_current_time() - philo->thread_create, philo->id, COLOR_RESET);
	usleep(philo->program->time_to_eat);
	philo->eat_count++;
	philo->left_fork = 0;
	philo->right_fork = 0;
}

void	think(t_philo *philo)
{
	printf("%s%dms %d is thinking%s\n", COLOR_CYAN, get_current_time() - philo->thread_create, philo->id, COLOR_RESET);
	while (!philo->left_fork || !philo->right_fork)
	{
		if (!philo->left_fork)
		{
			philo->left_fork = 1;
			printf("%s%dms %d has taken a fork%s\n", COLOR_GREEN, get_current_time() - philo->thread_create, philo->id, COLOR_RESET);
		}
		if (!philo->right_fork)
		{
			philo->right_fork = 1;
			printf("%s%dms %d has taken a fork%s\n", COLOR_GREEN, get_current_time() - philo->thread_create, philo->id, COLOR_RESET);
		}
	}
}

// log format "timestamp_in_ms X died"
void	*philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->eat_count = 0;
	while (philo->eat_count < philo->program->must_eat_count)
	{
		// think(philo);
		eat(philo);
		printf("eat_count: %d\n", philo->eat_count);
		sleep_philo(philo);
		philo->eat_count++;
	}
	printf("%s%dms %d died%s\n", COLOR_RED, get_current_time() - philo->thread_create, philo->id, COLOR_RESET);
	return (NULL);
}
