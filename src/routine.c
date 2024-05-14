#include "../includes/philo.h"
/*
void	set_fork(t_philos *philo, int new_status, int fork)
{
	pthread_mutex_lock(&philo->set_fork);
	if (fork == 0)
		philo->get_fork_left = new_status;
	else if (fork == 1)
		philo->get_fork_right = new_status;
	pthread_mutex_unlock(&philo->set_fork);
}
*/
int	philo_alive(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->table_mutex);
	if (philo->data->end_dinner == 1)
	{
		pthread_mutex_unlock(&philo->data->table_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->table_mutex);
	pthread_mutex_lock(&philo->dead_check);
	if (philo->status == 0)
	{
		pthread_mutex_unlock(&philo->dead_check);
		return (0);
	}
	pthread_mutex_unlock(&philo->dead_check);
	return (1);
}

void	new_time_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->dead_check);
	philo->last_time_eat = get_real_time();
	pthread_mutex_unlock(&philo->dead_check);
}

void	add_another_meal(t_philos *philo)
{
	pthread_mutex_lock(&philo->meal_check);
	philo->i_eat++;
	pthread_mutex_unlock(&philo->meal_check);
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
	print_status("is eating\n", (get_real_time() - philo->data->time_start)
		/ 1000, philo->index, &(philo->data->print_mutex));
	new_sleep(philo->data->time_eat);
	new_time_eat(philo);
	add_another_meal(philo);
	unlock_forks(philo);
	return (1);
}

int	philo_eat_all(t_philos *philo)
{
	pthread_mutex_lock(&philo->meal_check);
	if (philo->i_eat == philo->data->times_must_eat)
	{
		pthread_mutex_unlock(&philo->meal_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_check);
	return (0);
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
	t_philos *philo;

	philo = (t_philos *)arg;
	
	// wait_start_simulation(philo->data);
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
