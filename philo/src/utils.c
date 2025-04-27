/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:13:06 by Hadia             #+#    #+#             */
/*   Updated: 2025/04/27 17:05:22 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int ft_atoi(const char *nptr)
{
        int i = 0;
        int r = 0;
        int sign = 1;

        while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
                i++;
        if (nptr[i] == '-' || nptr[i] == '+')
        {
                if (nptr[i] == '-')
                        sign = sign * -1;
                i++;
        }
        while (nptr[i] >= '0' && nptr[i] <= '9')
        {
                r = r * 10 + (nptr[i] - '0');
                i++;
        }
        return (r * sign);
}

time_t get_time_ms(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status)
{
    long	time;
    
    time = get_time_ms() - philo->room->start_time;
    printf("%ld %d %s\n", time, philo->id, status);
}
