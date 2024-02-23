/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intra <intra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:40:18 by intra             #+#    #+#             */
/*   Updated: 2024/02/23 09:35:05 by intra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	input_invalid(char argc, char **argv)
{
	if (argc < 5 || argc > 6 || !is_all_numbers(argv))
	{
		printf("%sUsage: ./philo number_of_philosophers time_to_die \
		time_to_eat time_to_sleep  \
		[number_of_times_each_philosopher_must_eat%s\n",
			COLOR_RED, COLOR_RESET);
		return (1);
	}
	return (0);
}

void	unlock_after_end(t_philo *philo)
{
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->id + 1]);
}
