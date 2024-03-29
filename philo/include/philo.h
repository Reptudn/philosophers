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
# include <sys/time.h>

# include "colors.h"

# define PTHREAD_THREADS_MAX 200
# define SECOND 1000000

typedef struct s_philo
{
	int					id;
	long				thread_create;
	int					eat_count;
	long				last_eat;
	pthread_mutex_t		last_eat_mutex;
	pthread_mutex_t		eat_count_mutex;
	struct s_program	*program;
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
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*dead_mutex;
	t_philo			*philos;
}				t_program;

void	*philosopher(void *args);
void	*monitor(void *args);

void	print_action(t_philo *philo, char *action, char *color);
void	take_left_fork(t_philo *philo);
void	take_right_fork(t_philo *philo);

void	destroy(t_program *program, int i);
int		setup(char **argv, t_program *program);
int		is_all_numbers(char **args);
int		input_invalid(char argc, char **argv);
int		make_dead_mutex(t_program *program);

void	unlock_after_end(t_philo *philo);

int		ft_atoi(const char *nptr);
long	get_current_time(void);
int		ft_usleep(int time_in_ms);
float	get_converted_time(long start);
int		is_number(const char *nptr);
int		is_dead(t_program *program);

#endif