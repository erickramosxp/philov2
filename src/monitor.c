/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:23 by erramos           #+#    #+#             */
/*   Updated: 2024/05/16 12:50:16 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	disable_all_philos(t_philos *philos)
{
	int			i;
	t_philos	*temp;

	i = 0;
	temp = philos;
	while (i <= temp->data->nb_philo)
	{
		set_status(&temp->status, 0, &temp->dead_check);
		temp = temp->next;
		i++;
	}
}

int	philo_dead(t_philos *philo)
{
	pthread_mutex_lock(&philo->dead_check);
	if ((get_real_time() - philo->last_time_eat) > philo->data->time_die)
	{
		philo->status = 0;
		pthread_mutex_unlock(&philo->dead_check);
		disable_all_philos(philo);
		set_status(&philo->data->end_dinner, 1, &philo->data->table_mutex);
		print_status("\033[31mdied\033[0m\n",
			(get_real_time() - philo->data->time_start)
			/ 1000, philo->index, &(philo->data->print_mutex));
		return (1);
	}
	pthread_mutex_unlock(&philo->dead_check);
	return (0);
}

int	verify_all_philos_eat(t_philos *philo)
{
	t_philos	*temp;
	int			i;

	temp = philo;
	i = 0;
	while (i < temp->data->nb_philo)
	{
		pthread_mutex_lock(&philo->meal_check);
		if (philo->i_eat != philo->data->times_must_eat)
		{
			pthread_mutex_unlock(&philo->meal_check);
			return (0);
		}
		pthread_mutex_unlock(&philo->meal_check);
		i++;
		temp = temp->next;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		if (philo_dead(philo))
			break ;
		if (philo->data->flag_can_eat == 1)
			if (verify_all_philos_eat(philo))
				break ;
		philo = philo->next;
	}
	return (NULL);
}
