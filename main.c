/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:53:16 by erramos           #+#    #+#             */
/*   Updated: 2024/05/04 00:27:55 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	start_routine(t_data *data)
{
	int			nb_philos;
	int			i;
	t_philos	*philo;

	philo = data->philo;
	i = 0;
	nb_philos = data->nb_philo;
	while (i < nb_philos)
	{
		pthread_create(&philo->philo, NULL, &filosofo, philo);
		philo = philo->next;
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
		i++;
	}
	pthread_join(data->monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!valid_args(argc - 1, argv + 1))
		return (1);
	init_infos(&data, argv, argc);
	pthread_create(&data.monitor, NULL, &monitor, data.philo);
	start_routine(&data);
	return (0);
}
