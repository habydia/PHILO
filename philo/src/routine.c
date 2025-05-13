/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:35:58 by hvby              #+#    #+#             */
/*   Updated: 2025/05/08 20:26:36 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	sleeping(t_philo *philo)
{
	if (!philo->room->philo_dead)
		print_status(philo, "is sleeping");
	usleep(philo->room->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	if (!philo->room->philo_dead)
		print_status(philo, "\033[0;35mis thinking\033[0m");
}

// Calculate fork indices
// Take forks (lock mutexes)
// Eat
// Release forks (unlock mutexes)
void	eat(t_philo *philo)
{
	unsigned int	left_fork;
	unsigned int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->room->number_of_philosopers;
	pthread_mutex_lock(&philo->room->forks[left_fork]);
	pthread_mutex_lock(&philo->room->forks[right_fork]);
	print_status(philo, "\033[0;33mhas taken the forks\033[0m");
	print_status(philo, "\e[1;34mis eating\e[0m");
	pthread_mutex_lock(&philo->room->death_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->room->death_mutex);
	usleep(philo->time_spent_eating * philo->room->time_to_eat);
	pthread_mutex_unlock(&philo->room->forks[left_fork]);
	pthread_mutex_unlock(&philo->room->forks[right_fork]);
	print_status(philo, "\033[0;32mput the forks down\033[0m");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (!philo->room->philo_dead)
	{
		think(philo);
		eat(philo);
		sleeping(philo);
		if (check_death(philo))
			break ;
	}
	return (NULL);
}
