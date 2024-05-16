/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:12 by erramos           #+#    #+#             */
/*   Updated: 2024/05/16 12:37:13 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	verif_is_numeric(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_limits(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_atoi(args[i]) < 60)
		{
			if (i < 4)
			{
				printf("Enter time greater than 60 ms.\n");
				return (0);
			}
		}
		i++;
	}
	if (ft_atoi(args[0]) > 200)
	{
		printf("Enter number of philosophers of 200 or less.\n");
		return (0);
	}
	return (1);
}

int	valid_args(int argc, char **args)
{
	int	i;

	i = 0;
	if (argc < 4 || argc > 5)
	{
		printf("Erro\n");
		return (0);
	}
	while (args[i])
	{
		if (!verif_is_numeric(args[i]))
		{
			printf("Erro\n");
			return (0);
		}
		i++;
	}
	if (ft_atoi(args[0]) <= 0)
	{
		printf("Erro\n");
		return (0);
	}
	if (!valid_limits(args))
		return (0);
	return (1);
}
