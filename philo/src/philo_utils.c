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