/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:29:53 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/09 17:55:28 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*behav(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->times--)
	{
		iter(philo);
		pthread_mutex_lock(&philo->args->_dead);
		if (philo->args->dead)
		{
			pthread_mutex_unlock(&philo->args->_dead);
			break ;
		}
		pthread_mutex_unlock(&philo->args->_dead);
	}
	return (NULL);
}

int	ft_free(t_philo *philos, pthread_mutex_t **forks, int nbr)
{
	int	i;

	i = 0;
	if (philos)
	{
		while (i < nbr)
			free(philos[i++].thread);
		free(philos);
	}
	i = 0;
	if (forks)
	{
		while (i < nbr)
		{
			pthread_mutex_destroy(forks[i]);
			free(forks[i]);
			i++;
		}
		free(forks);
	}
	return (0);
}

pthread_mutex_t	**init_forks(int nbr)
{
	pthread_mutex_t	**forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * nbr);
	if (!forks)
		return (NULL);
	while (i < nbr)
	{
		forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (ft_free(NULL, forks, i), NULL);
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (forks);
}

static int	init_philos(t_philo *philos, pthread_mutex_t **forks, t_arg *a)
{
	int	i;

	i = -1;
	while (++i < a->nbr_philo)
	{
		philos[i].pos = i + 1;
		philos[i].fork[0] = forks[i];
		philos[i].fork[1] = forks[(i + 1) % a->nbr_philo];
		philos[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philos[i].thread)
			return (0);
		philos[i].args = a;
		philos[i].last_meal = 0;
		philos[i].philos = philos;
		philos[i].forks = forks;
		philos[i].times = a->times;
	}
	gettimeofday(&a->start, NULL);
	if (!loop_thread(philos))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	**forks;
	t_arg			args;
	int				i;
	int				pars;

	pars = parsing(argc, argv);
	if (!pars)
		return (printf("Error\n"), 1);
	else if (pars == -1)
		return (0);
	if (ft_atoi(argv[1]) == 0)
		return (0);
	init_args(argc, argv, &args);
	philos = (t_philo *)malloc(sizeof(t_philo) * args.nbr_philo);
	forks = init_forks(args.nbr_philo);
	if (!philos || !forks)
		return (ft_free(NULL, forks, args.nbr_philo), 2);
	if (!init_philos(philos, forks, &args))
		return (ft_free(philos, forks, args.nbr_philo), 3);
	i = 0;
	while (i < args.nbr_philo)
		pthread_join(*philos[i++].thread, NULL);
	ft_free(philos, forks, args.nbr_philo);
	return (0);
}
