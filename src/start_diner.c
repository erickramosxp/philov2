#include "../includes/philo.h"

void	*start_alone_diner(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->fork);
	print_status("has taken a fork\n", (get_real_time()
			- philo->data->time_start) / 1000, philo->index,
		&(philo->data->print_mutex));
	usleep(philo->data->time_die);
	pthread_mutex_unlock(&philo->fork);
	return (NULL);
}

void	start_dinner(t_philos *philo)
{
	int	i;
	int	nb_philos;

	i = 0;
	nb_philos = philo->data->nb_philo;
	while (i < nb_philos)
	{
		pthread_create(&philo->philo, NULL, &filosofo, philo);
		philo = philo->next;
		usleep(450);
		i++;
	}
	pthread_create(&philo->data->monitor, NULL, &monitor, philo->data->philo);
	i = 0;
	while (i < nb_philos)
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
		i++;
	}
	pthread_join(philo->data->monitor, NULL);
}

void	start_routine(t_data *data)
{
	t_philos	*philo;

	philo = data->philo;
	if (data->nb_philo == 1)
	{
		pthread_create(&philo->philo, NULL, &start_alone_diner, philo);
		pthread_join(philo->philo, NULL);
	}
	else
		start_dinner(philo);
}
