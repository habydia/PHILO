/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:13:06 by Hadia             #+#    #+#             */
/*   Updated: 2025/05/07 20:42:20 by hadia            ###   ########.fr       */
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
    printf("\033[0;36m%ld\033[0m \033[37;1m%d\033[0m %s\n", time, philo->id, status);
}
int check_death(t_philo *philo)
{
    if ( philo->last_meal_time >= philo->room->time_to_die)
    {
        pthread_mutex_lock(&philo->room->death_mutex);
        if (!philo->room->philo_dead)
        {
            print_status(philo, "\033[0;31mdied\033[0m");
            philo->room->philo_dead = 1;
        }
        pthread_mutex_unlock(&philo->room->death_mutex);
        return (1);
    }
    return (0);
}
