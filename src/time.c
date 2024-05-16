/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:00:56 by erramos           #+#    #+#             */
/*   Updated: 2024/05/16 13:01:33 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_real_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000000) + tv.tv_usec;
	return (time);
}

int	new_sleep(long time)
{
	long	new_time;

	new_time = get_real_time() + time;
	while (get_real_time() < new_time)
	{
		usleep(100);
	}
	return (1);
}
