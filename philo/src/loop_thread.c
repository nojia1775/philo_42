/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:18:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/06 16:23:55 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	loop_thread(t_philo *philos)
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
