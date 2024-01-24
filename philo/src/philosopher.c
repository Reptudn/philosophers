/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/01/24 19:00:36 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
# include <unistd.h>

void	sleep(t_philo *philo)
{
	printf("%d is sleeping\n", philo->id);
	usleep(100); //later with real sleep time
}

void	eat(t_philo *philo)
{
	if (!philo->left_fork)
	{
		philo->left_fork = 1;
		printf("%d has taken a fork\n", philo->id);
		if (!philo->right_fork)
		{
			philo->right_fork = 1;
			printf("%d has taken a fork\n", philo->id);
		}
	}
	if (philo->left_fork || philo->right_fork)
	{
		printf("%d is eating\n", philo->id);
		philo->left_fork = 0;
		philo->right_fork = 0;
	}
	// printf("%d is eating\n", philo->id);
}

void	think(t_philo *philo)
{
	printf("%d is thinking\n", philo->id);
}

void	*philosopher(void *args)
{
	pthread_t		thread;
	int				alive;

	alive = 1;
	while (alive)
	{
		think((t_philo *)args);
	}
	pthread_join(thread, NULL);
}
