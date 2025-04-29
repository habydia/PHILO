/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:35:58 by hvby              #+#    #+#             */
/*   Updated: 2025/04/29 16:04:11 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void	sleeping(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->room->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
    print_status(philo, "\033[0;35mis thinking\033[0m");
}

void	eat(t_philo *philo)
{
    unsigned int left_fork;
    unsigned int right_fork;
    
    // Calculate fork indices
    left_fork = philo->id - 1;
    right_fork = (philo->id) % philo->room->number_of_philosopers;
    
    // Take forks (lock mutexes)
    pthread_mutex_lock(&philo->room->forks[left_fork]);
    print_status(philo, "\033[0;33mhas taken a fork\033[0m");
    pthread_mutex_lock(&philo->room->forks[right_fork]);
    print_status(philo, "\033[0;33mhas taken a fork\033[0m");
    
    // Eat
    print_status(philo, "\e[1;34mis eating\e[0m");
    philo->last_meal_time = get_time_ms();
    usleep(philo->room->time_to_eat * 1000);
    philo->meals_eaten++;
    // Release forks (unlock mutexes)
    pthread_mutex_unlock(&philo->room->forks[left_fork]);
    pthread_mutex_unlock(&philo->room->forks[right_fork]);
    print_status(philo, "\033[0;32mput the forks down\033[0m");
    print_status(philo, "\033[0;32mput the forks down\033[0m");
}

void *routine(void *arg)
{

    t_philo *philo;
    
    philo = (t_philo *)arg;
    philo->room->start_time = get_time_ms();
    philo->alive = true;
    
    // If odd numbered philo, wait a bit to avoid deadlock
    if (philo->id % 2 != 0)
        usleep(1000);
    
    while (philo->alive)
    {
        think(philo);
        eat(philo);
        sleeping(philo);

        if(philo->last_meal_time >= philo->room->time_to_die)
        {
            print_status(philo, "\033[0;31mdied\033[0m");
            philo->alive = false;
            break;
        }
    }
    
    return NULL;
}