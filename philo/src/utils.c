/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:29:58 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/09 15:04:39 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

size_t	ft_strlen(char *str)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			len++;
		i++;
	}
	return (len);
}

void	my_printf(int text, t_philo *philo)
{
	char	*str[5];
	char	*colors[5];

	if (philo->args->dead && text != 3)
		return ;
	get_time(philo);
	str[0] = "is thinking";
	str[1] = "is eating";
	str[2] = "is sleeping";
	str[3] = "died";
	str[4] = "has taken a fork";
	colors[0] = MAG;
	colors[1] = GREEN;
	colors[2] = BLUE;
	colors[3] = RED;
	colors[4] = "";
	pthread_mutex_lock(&philo->args->_print);
	pthread_mutex_lock(&philo->args->_spend);
	printf("%s%ld %d %s%s\n", colors[text], philo->args->spend,
		philo->pos, str[text], RESET);
	pthread_mutex_unlock(&philo->args->_print);
	pthread_mutex_unlock(&philo->args->_spend);
}

void	meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->_spend);
	philo->last_meal = philo->args->spend;
	pthread_mutex_unlock(&philo->args->_spend);
}
