/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:44:43 by intra             #+#    #+#             */
/*   Updated: 2024/01/30 11:23:11 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	sleep_philo(t_philo *philo)
// {
// 	printf("%s%d is sleeping%s\n", COLOR_BLUE, philo->id, COLOR_RESET);
// 	usleep(100); //later with real sleep time
// }

// void	eat(t_philo *philo)
// {
// 	if (!philo->left_fork)
// 	{
// 		philo->left_fork = 1;
// 		printf("%s%d has taken a fork%s\n", COLOR_GREEN, philo->id, COLOR_RESET);
// 		if (!philo->right_fork)
// 		{
// 			philo->right_fork = 1;
// 			printf("%s%d has taken a fork%s\n", COLOR_GREEN, philo->id, COLOR_RESET);
// 		}
// 	}
// 	if (philo->left_fork || philo->right_fork)
// 	{
// 		printf("%s%d is eating%s\n", COLOR_MAGENTA, philo->id, COLOR_RESET);
// 		philo->left_fork = 0;
// 		philo->right_fork = 0;
// 	}
// 	// printf("%d is eating\n", philo->id);
// }

// void	think(t_philo *philo)
// {
// 	printf("%d is thinking\n", philo->id);
// }

void	*philosopher(void *args)
{
	// int				alive;
	// int				run;

	// alive = 1;
	// run = 1;
	// while (alive || run)
	// {
	// 	think((t_philo *)args);
	// }
	// if (!alive)
	// 	printf("%s%d died%s\n", COLOR_RED, ((t_philo *)args)->id, COLOR_RESET);
	printf("%sHello, i'm a thread!%s\n", COLOR_BLUE, COLOR_RESET);
	return (NULL);
}
