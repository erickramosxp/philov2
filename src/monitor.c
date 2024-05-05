#include "../includes/philo.h"

int	philo_dead(t_philos *philo)
{
	pthread_mutex_lock(&philo->set_status);
	if ((get_real_time() - philo->last_time_eat) > philo->data->time_die)
	{
		philo->status = 0;
		philo->data->end_dinner = 1;
		pthread_mutex_unlock(&philo->set_status);
		return (1);
	}
	pthread_mutex_unlock(&philo->set_status);
	return (0);
}

int	verify_philo_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->set_status);
	if (philo->i_eat == philo->data->times_must_eat)
	{
		philo->status = 2;
	}
	pthread_mutex_unlock(&philo->set_status);
	return (0);
}

void	*monitor(void *arg)
{
	t_philos *philo;

	philo = (t_philos *)arg;
	while (1)
	{
		if (philo_dead(philo))
			break ;
		if (philo->data->flag_can_eat == 1)
			verify_philo_eat(philo);
		philo = philo->next;
	}
	return (NULL);
}