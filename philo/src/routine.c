/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:35:58 by hvby              #+#    #+#             */
/*   Updated: 2025/05/07 18:38:22 by Hadia            ###   ########.fr       */
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
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 != 0)
        usleep(1000);

    while (1)
    {
        // Vérifier si quelqu'un est mort
        pthread_mutex_lock(&philo->room->death_mutex);
        if (philo->room->philo_dead)
        {
            pthread_mutex_unlock(&philo->room->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->room->death_mutex);

        think(philo);
        eat(philo);
        sleeping(philo);

        if (philo->last_meal_time >= philo->room->time_to_die)
        {
            pthread_mutex_lock(&philo->room->death_mutex);
            if (!philo->room->philo_dead)
            {
                print_status(philo, "\033[0;31mdied\033[0m");
                philo->room->philo_dead = 1;
            }
            pthread_mutex_unlock(&philo->room->death_mutex);
            break;
        }
    }
    return NULL;
}
