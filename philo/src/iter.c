/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:29:46 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/09 14:39:08 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	get_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->_cur);
	pthread_mutex_lock(&philo->args->_spend);
	gettimeofday(&philo->args->cur, NULL);
	philo->args->spend = (philo->args->cur.tv_sec
			- philo->args->start.tv_sec) * 1000
		+ (philo->args->cur.tv_usec
			- philo->args->start.tv_usec) / 1000;
	pthread_mutex_unlock(&philo->args->_cur);
	pthread_mutex_unlock(&philo->args->_spend);
}

static int	isdead(t_philo *philo)
{
	get_time(philo);
	pthread_mutex_lock(&philo->args->_dead);
	if (philo->args->dead)
		return (pthread_mutex_unlock(&philo->args->_dead), 1);
	pthread_mutex_lock(&philo->args->_spend);
	if (philo->args->spend - philo->last_meal > philo->args->time_die)
	{
		philo->args->dead = 1;
		pthread_mutex_unlock(&philo->args->_spend);
		my_printf(3, philo);
		pthread_mutex_unlock(&philo->args->_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->_dead);
	pthread_mutex_unlock(&philo->args->_spend);
	return (0);
}

static void	mutex(t_philo *philo, int lock)
{
	if (lock)
	{
		pthread_mutex_lock(philo->fork[philo->pos % 2]);
		if (isdead(philo))
		{
			pthread_mutex_unlock(philo->fork[philo->pos % 2]);
			return ;
		}
		my_printf(4, philo);
		pthread_mutex_lock(philo->fork[(philo->pos + 1) % 2]);
		if (isdead(philo))
		{
			pthread_mutex_unlock(philo->fork[philo->pos % 2]);
			pthread_mutex_unlock(philo->fork[(philo->pos + 1) % 2]);
			return ;
		}
		my_printf(4, philo);
		my_printf(1, philo);
	}
	else
	{
		pthread_mutex_unlock(philo->fork[philo->pos % 2]);
		pthread_mutex_unlock(philo->fork[(philo->pos + 1) % 2]);
	}
}

void	iter(t_philo *philo)
{
	if (isdead(philo))
		return ;
	my_printf(0, philo);
	mutex(philo, 1);
	meal(philo);
	if (isdead(philo))
		return ;
	usleep(philo->args->time_eat * 1000);
	mutex(philo, 0);
	my_printf(2, philo);
	if (isdead(philo))
		return ;
	usleep(philo->args->time_sleep * 1000);
	if (isdead(philo))
		return ;
}
