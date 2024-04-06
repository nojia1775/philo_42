/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:30:01 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/06 16:22:32 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include "color.h"

typedef struct s_philo  t_philo;
typedef struct s_arg    t_arg;

int             ft_atoi(const char *nptr);
size_t  ft_strlen(char *str);
int             parsing(int argc, char **argv);
void    init_args(int argc, char **argv, t_arg *args);
void    get_time(t_philo *philo);
void    iter(t_philo *philo);
int             ft_free(t_philo *philos, pthread_mutex_t **forks, int nbr);
void    my_printf(int text, t_philo *philo, int lock);
void	meal(t_philo *philo);
void     *behav(void *arg);
int	loop_thread(t_philo *philos);

struct s_arg
{
        int             nbr_philo;
        pthread_mutex_t _nbr_philo;
        int             time_die;
        pthread_mutex_t _time_die;
        int             time_eat;
        pthread_mutex_t _time_eat;
        int             time_sleep;
        pthread_mutex_t _time_sleep;
        int             dead;
        pthread_mutex_t _dead;
        int             times;
        pthread_mutex_t _times;
        struct timeval  start;
        pthread_mutex_t _start;
        struct timeval  cur;
        pthread_mutex_t _cur;
        pthread_mutex_t _print;
        long            spend;
        pthread_mutex_t _spend;
};

struct  s_philo
{
        pthread_t       *thread;
        int             pos;
        pthread_mutex_t *fork[2];
        t_arg           *args;
        t_philo         *philos;
        pthread_mutex_t **forks;
        int             last_meal;
        int             times;
};

#endif