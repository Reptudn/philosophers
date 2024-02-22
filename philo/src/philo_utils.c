#include "../include/philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

void	print_action(t_philo *philo, char *action, char *color)
{
	pthread_mutex_lock(philo->program->print_mutex);
	if (philo->program->dead == 1)
	{
		pthread_mutex_unlock(philo->program->print_mutex);
		return ;
	}
	printf("%s%.2fms %d %s%s\n", color,
			get_converted_time(philo->thread_create),
			philo->id + 1, action, COLOR_RESET);
	pthread_mutex_unlock(philo->program->print_mutex);
}

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->forks[philo->id]);
	print_action(philo, "has taken left fork", COLOR_GREEN);
}

void	take_right_fork(t_philo *philo)
{
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->program->forks[0]);
	else
		pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
	print_action(philo, "has taken right fork", COLOR_GREEN);
}