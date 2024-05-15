#include "../includes/philo.h"

int	taken_left_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->previous->fork);
	if (philo_alive(philo))
	{
		print_status("has taken a fork\n", (get_real_time()
				- philo->data->time_start) / 1000, philo->index,
			&(philo->data->print_mutex));
		return (1);
	}
	return (0);
}

int	taken_right_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (philo_alive(philo))
	{
		print_status("has taken a fork\n", (get_real_time()
				- philo->data->time_start) / 1000, philo->index,
			&(philo->data->print_mutex));
		return (1);
	}
	return (0);
}

void	unlock_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->previous->fork);
	pthread_mutex_unlock(&philo->fork);
}
