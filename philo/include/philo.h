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
# include <sys/_pthread/_pthread_mutex_t.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/_types/_timeval.h>

# include "colors.h"

# define PTHREAD_THREADS_MAX 512
# define SECOND 1000000

typedef struct s_philo
{
	pthread_t			thread_id;
	int					id;
	int					left_fork;
	int					right_fork;
	int					thread_create;
	int					eat_count;
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
	pthread_mutex_t	*forks;
	t_philo			*philos;
}				t_program;

void	*philosopher(void *args);
void	*monitor(void *args);

int		ft_atoi(const char *nptr);
int		get_current_time(void);
void	ft_usleep(int time_in_ms);
float	get_converted_time(int start);

#endif