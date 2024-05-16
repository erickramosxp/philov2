/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:38:00 by erramos           #+#    #+#             */
/*   Updated: 2024/05/16 12:38:01 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(char *msg, long time_current, int index_philo,
		t_mutex *print_mutex)
{
	pthread_mutex_lock(print_mutex);
	printf("%ld %d %s", time_current, index_philo, msg);
	pthread_mutex_unlock(print_mutex);
}

void	set_status(int *status, int new_status, t_mutex *status_mutex)
{
	pthread_mutex_lock(status_mutex);
	*status = new_status;
	pthread_mutex_unlock(status_mutex);
}

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

void	add_another_meal(t_philos *philo)
{
	pthread_mutex_lock(&philo->meal_check);
	philo->i_eat++;
	pthread_mutex_unlock(&philo->meal_check);
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
