#include "../includes/philo.h"

void	new_time_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->dead_check);
	philo->last_time_eat = get_real_time();
	pthread_mutex_unlock(&philo->dead_check);
}

int	philo_eat(t_philos *philo)
{
	if (!taken_left_fork(philo))
	{
		pthread_mutex_unlock(&philo->previous->fork);
		return (0);
	}
	if (!taken_right_fork(philo))
	{
		pthread_mutex_unlock(&philo->previous->fork);
		pthread_mutex_unlock(&philo->fork);
		return (0);
	}
	print_status("\033[32mis eating\033[0m\n",
		(get_real_time() - philo->data->time_start)
		/ 1000, philo->index, &(philo->data->print_mutex));
	new_sleep(philo->data->time_eat);
	new_time_eat(philo);
	add_another_meal(philo);
	unlock_forks(philo);
	return (1);
}

int	philo_sleep(t_philos *philo)
{
	if (philo->data->flag_can_eat && philo_eat_all(philo))
		return (0);
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
	t_philos	*philo;

	philo = (t_philos *)arg;

	if (philo->index % 2 == 0)
		usleep(200);
	while (1)
	{
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (NULL);
}
