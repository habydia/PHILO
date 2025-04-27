/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:35:58 by hvby              #+#    #+#             */
/*   Updated: 2025/04/27 17:21:28 by Hadia            ###   ########.fr       */
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
    print_status(philo, "is thinking");
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
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->room->forks[right_fork]);
    print_status(philo, "has taken a fork");
    
    // Eat
    print_status(philo, "is eating");
    philo->last_meal_time = get_time_ms();
    usleep(philo->room->time_to_eat * 1000);
    philo->meals_eaten++;
    
    // Release forks (unlock mutexes)
    pthread_mutex_unlock(&philo->room->forks[left_fork]);
    pthread_mutex_unlock(&philo->room->forks[right_fork]);
}

void *routine(void *arg)
{

    t_philo *philo;
    int alive;
    
    philo = (t_philo *)arg;
    philo->room->start_time = get_time_ms();
    alive = 1;
    
    // If odd numbered philo, wait a bit to avoid deadlock
    if (philo->id % 2 != 0)
        usleep(1000);
    
    while (alive)
    {
        think(philo);
        eat(philo);
        sleeping(philo);
        
        // Check if simulation should continue
        // This will need to be implemented with proper death checking
    }
    
    return NULL;
}