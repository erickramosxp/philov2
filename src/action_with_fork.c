#include "../includes/philo.h"

int	taken_left_fork(t_philos *philo)
{
//	set_fork(philo, 1, 0);
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
//	set_fork(philo, 1, 1);
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
/*
int	have_right_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->set_fork);
	if (philo->get_fork_right == 1)
	{
		pthread_mutex_unlock(&philo->set_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->set_fork);
	return (0);
}

int	have_left_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->set_fork);
	if (philo->get_fork_left == 1)
	{
		pthread_mutex_unlock(&philo->set_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->set_fork);
	return (0);
}
*/
void	unlock_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->previous->fork);
	pthread_mutex_unlock(&philo->fork);
}
