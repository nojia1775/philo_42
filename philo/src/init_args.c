/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:15:54 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/06 18:34:53 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_mutexes(t_arg *args)
{
	pthread_mutex_init(&args->_cur, NULL);
	//pthread_mutex_init(&args->_nbr_philo, NULL);
	//pthread_mutex_init(&args->_time_die, NULL);
	//pthread_mutex_init(&args->_time_eat, NULL);
	//pthread_mutex_init(&args->_time_sleep, NULL);
	pthread_mutex_init(&args->_dead, NULL);
	//pthread_mutex_init(&args->_start, NULL);
	pthread_mutex_init(&args->_print, NULL);
	pthread_mutex_init(&args->_spend, NULL);
}

void	init_args(int argc, char **argv, t_arg *args)
{
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	args->dead = 0;
	if (argc == 6)
		args->times = ft_atoi(argv[5]);
	else
		args->times = -1;
	args->spend = 0;
	init_mutexes(args);
}
