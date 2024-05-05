#include "../includes/philo.h"


int	philo_alive(t_philos *philo)
{
	pthread_mutex_lock(&philo->set_status);
	if (philo->data->end_dinner == 1 || philo->status == 0)
	{
		pthread_mutex_unlock(&philo->set_status);
		return (0);
	}
	pthread_mutex_unlock(&philo->set_status);
	return (1);
}

int	taken_left_fork(t_philos *philo)
{
	if (philo_alive(philo))
	{
		pthread_mutex_lock(&philo->previous->fork);
		print_status("has taken a fork\n", (get_real_time()
				- philo->data->time_start) / 1000, philo->index,
			&(philo->data->print_mutex));
		return (1);
	}
	return (0);
}

int	taken_right_fork(t_philos *philo)
{
	if (philo_alive(philo))
	{
		pthread_mutex_lock(&philo->fork);
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

int	philo_eat(t_philos *philo)
{
	if (!taken_left_fork(philo))
		return (0);
	if (!taken_right_fork(philo))
		return (0);
	print_status("is eating\n", (get_real_time() - philo->data->time_start)
		/ 1000, philo->index, &(philo->data->print_mutex));
	new_sleep(philo->data->time_eat);
	philo->last_time_eat = get_real_time();
	philo->i_eat++;
	unlock_forks(philo);
	return (1);
}
int	philo_sleep(t_philos *philo)
{
	if (!philo_alive(philo))
		return (0);
	print_status("is sleeping\n", (get_real_time() - philo->data->time_start)
		/ 1000, philo->index, &(philo->data->print_mutex));
	usleep(philo->data->time_sleep);
	return (1);
}

int	philo_think(t_philos *philo)
{
	if (!philo_alive(philo))
		return (0);
	print_status("is thinking\n", (get_real_time() - philo->data->time_start)
		/ 1000, philo->index, &(philo->data->print_mutex));
	return (1);
}

void	*filosofo(void *arg)
{
	t_philos *philo;

	philo = (t_philos *)arg;
	if (philo->index % 2 == 0)
		usleep(1500);
	while (1)
	{
		if (!philo_think(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
	}
	return (NULL);
}