#include "../includes/philo.h"

t_philos	*malloc_philos(int qtd_philos)
{
	t_philos	*philo;
	t_philos	*prev;
	t_philos	*head;

	prev = NULL;
	head = NULL;
	while (qtd_philos--)
	{
		philo = malloc(sizeof(t_philos));
		if (!philo)
			return (NULL);
		philo->previous = prev;
		if (prev)
			prev->next = philo;
		if (!head)
			head = philo;
		prev = philo;
		if (qtd_philos == 0)
		{
			philo->next = head;
			head->previous = philo;
		}
	}
	return (head);
}

void	index_philos(t_philos *philo, int qtd_philos)
{
	int	i;

	i = 1;
	while (i <= qtd_philos)
	{
		philo->index = i;
		philo->status = 1;
		philo->i_eat = 0;
		philo->last_time_eat = get_real_time();
		pthread_mutex_init(&philo->fork, NULL);
		pthread_mutex_init(&philo->set_status, NULL);
		philo = philo->next;
		i++;
	}
}

void	link_philos(t_data *data, t_philos *philos)
{
	int	nb_philos;
	int	i;

	nb_philos = data->nb_philo;
	i = 0;
	while (i < nb_philos)
	{
		philos->data = data;
		philos = philos->next;
		i++;
	}
}

void	init_infos(t_data *data, char **args, int argc)
{
	data->nb_philo = ft_atoi(args[1]);
	data->time_die = ft_atoi(args[2]) * 1000;
	data->time_eat = ft_atoi(args[3]) * 1000;
	data->time_sleep = ft_atoi(args[4]) * 1000;
	data->time_start = get_real_time();
	data->philos_dead = data->nb_philo;
	data->end_dinner = 0;
	if (argc == 6)
	{
		data->times_must_eat = ft_atoi(args[5]);
		data->flag_can_eat = 1;
	}
	else
	{
		data->times_must_eat = -1;
		data->flag_can_eat = 0;
	}
	data->philo = NULL;
	data->philo = malloc_philos(data->nb_philo);
	index_philos(data->philo, data->nb_philo);
	link_philos(data, data->philo);
	pthread_mutex_init(&data->table_mutex, NULL);
	pthread_mutex_init(&data->status_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}
