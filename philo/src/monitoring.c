/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:53:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/01/22 10:36:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

void	log_program(t_program *program)
{
	int	i;

	printf("\tProgram:\n");
	printf("number_of_philosophers: %d\n", program->number_of_philosophers);
	printf("time_to_die: %d\n", program->time_to_die);
	printf("time_to_eat: %d\n", program->time_to_eat);
	printf("time_to_sleep: %d\n", program->time_to_sleep);
	printf("must_eat_count: %d\n", program->must_eat_count);
	printf("dead: %d\n", program->dead);
	printf("\tPhilosophers:\n");
	i = -1;
	while (++i < program->number_of_philosophers)
	{
		printf("\tPhilosopher %d:\n", i);
		log_philo(&program->philos[i]);
		printf("------\n");
	}
}

void	log_philo(t_philo *philo)
{
	printf("id: %d\n", philo->id);
	printf("last_eat: %d\n", philo->last_eat);
	printf("meal_count: %d\n", philo->eat_count);
	printf("left_fork: %d\n", philo->left_fork);
	printf("right_fork: %d\n", philo->right_fork);
}
