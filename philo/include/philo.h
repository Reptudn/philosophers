/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:46:50 by jkauker           #+#    #+#             */
/*   Updated: 2024/01/22 10:35:56 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "colors.h"

# define PTHREAD_THREADS_MAX 512

typedef struct s_philo
{
	pthread_t		id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	int				last_eat;
	int				thread_create;
}				t_philo;

typedef struct s_program
{
	int				number_of_philosophers;
	int				current_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				dead;
	t_philo			*philos;
}				t_program;

void	*philosopher(void *args);

int		ft_atoi(const char *nptr);
void	log_philo(t_philo *philo);
void	log_program(t_program *program);

#endif