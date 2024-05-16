/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:51 by erramos           #+#    #+#             */
/*   Updated: 2024/05/16 13:01:56 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	resp;
	int	signal;
	int	i;

	i = 0;
	resp = 0;
	signal = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signal = signal *(-1);
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		resp = resp * 10 + (nptr[i] - '0');
		i++;
	}
	return (resp * signal);
}

long	ft_atol(const char *nptr)
{
	long	resp;
	long	signal;
	int		i;

	i = 0;
	resp = 0;
	signal = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signal = signal *(-1);
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		resp = resp * 10 + (nptr[i] - '0');
		i++;
	}
	return (resp * signal);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	free_list(t_philos *philo)
{
	t_philos	*temp;
	t_philos	*aux;

	temp = philo->next;
	while (temp != philo)
	{
		usleep(500);
		aux = temp->next;
		pthread_mutex_destroy(&temp->fork);
		pthread_mutex_destroy(&temp->meal_check);
		pthread_mutex_destroy(&temp->dead_check);
		free(temp);
		temp = aux;
	}
	pthread_mutex_destroy(&philo->data->table_mutex);
	pthread_mutex_destroy(&philo->data->print_mutex);
	free(philo);
}
