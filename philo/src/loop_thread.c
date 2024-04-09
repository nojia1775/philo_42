/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:18:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/09 18:26:43 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	loop(t_philo *philos)
{
	if (philos[0].args->nbr_philo % 2 == 0)
	{
		if (!loop_even(philos))
			return (0);
	}
	else
	{
		if (!loop_odd(philos))
			return (0);
	}
	return (1);
}

int	loop_odd(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].args->nbr_philo)
	{
		if (pthread_create(philos[i].thread, NULL, behav,
				&philos[i]))
			return (0);
		if (i + philos[0].args->nbr_philo - 1
			>= philos[0].args->nbr_philo - 1)
			i = i + philos[0].args->nbr_philo - 1
			- philos[0].args->nbr_philo - 1;
		else
			i += philos[0].args->nbr_philo - 1;
	}
	return (1);
}

int	loop_even(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].args->nbr_philo)
	{
		if (pthread_create(philos[i].thread, NULL, behav,
				&philos[i]))
			return (0);
		i += 2;
	}
	i = 1;
	while (i < philos[0].args->nbr_philo)
	{
		if (pthread_create(philos[i].thread, NULL, behav,
				&philos[i]))
			return (0);
		i += 2;
	}
	return (1);
}
