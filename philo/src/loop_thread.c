/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:18:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/09 18:40:57 by nadjemia         ###   ########.fr       */
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
		i++;
		usleep(philos[0].args->time_eat * 1000);
	}
	// if (pthread_create(philos[0].thread, NULL, behav,
	// 			&philos[0]))
	// 		return (0);
	// if (pthread_create(philos[philos[0].args->nbr_philo - 1].thread, NULL, behav,
	// 		&philos[philos[0].args->nbr_philo - 1]))
	// 	return (0);
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
