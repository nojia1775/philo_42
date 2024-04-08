/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:29:55 by nadjemia          #+#    #+#             */
/*   Updated: 2024/04/06 12:55:02 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int      spacebtw(char *str)
{
        int     i;
        int     space;
        int     nbr;

        i = 0;
        space = 0;
        nbr = 0;
        while (str[i])
        {
                if (str[i] >= '0' && str[i] <= '9')
                        nbr++;
                if (str[i] == ' ')
                        space++;
                if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
                        return (1);
                if (str[i] != ' ' && space != 0)
                        return (1);
                i++;
        }
        if (nbr == 0)
                return (1);
        return (0);
}

static int	isuint(char *str)
{
	int	len;
        int     i;

        i = 0;
        while (str[i] == ' ')
                i++;
        if (str[i] == '+')
                i++;
        while (str[i] == '0' && str[i + 1] == '0')
                i++;
	len = ft_strlen(str + i);
        if (spacebtw(str + i))
                return (0);
        if (len > 10)
                return (0);
	if (len == 10 && str[i] - '0' > 2)
		return (0);
	else if (len == 10 && str[i] == '2')
		if (ft_atoi(str + 1 + i) > 147483647)
			return (0);
	return (1);
}

static int      isvalid(char *str)
{
        if (*str == '\0' || !isuint(str))
                return (0);
        return (1);
}

int     parsing(int argc, char **argv)
{
        int     i;

        i = 1;
        if (argc < 5 || argc > 6)
                return (0);
        while (argv[i])
                if (!isvalid(argv[i++]))
                        return (0);
        if (ft_atoi(argv[1]) == 1)
        {
                usleep(ft_atoi(argv[2]) * 1000);
                return (printf("%s%d 1 died\n%s", RED, ft_atoi(argv[2]),
                        RESET), -1);
        }
        return (1);
}
