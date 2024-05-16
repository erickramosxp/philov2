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

int	main(int argc, char **argv)
{
	t_data	data;

	if (!valid_args(argc - 1, argv + 1))
		return (1);
	init_infos(&data, argv, argc);
	start_routine(&data);
	free_list(data.philo);
	return (0);
}
