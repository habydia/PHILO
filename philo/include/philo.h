/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:58 by hadia             #+#    #+#             */
/*   Updated: 2025/04/27 17:24:11 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

//data partagé 
typedef struct s_room 
{
    unsigned int number_of_philosopers; //number of fork
    pthread_mutex_t *forks;
    time_t time_to_die;
    time_t time_to_eat;
    time_t time_to_sleep;
    time_t  start_time;
} t_room;


//structure d'un philo
typedef struct s_philo
{
    pthread_t thread;
    unsigned int id;
    time_t last_meal_time;
    unsigned int meals_eaten;
    t_room *room;
}   t_philo;


//utils
time_t get_time_ms(void);
unsigned int ft_atoi(const char *nptr);
void	print_status(t_philo *philo, char *status);
void	think(t_philo *philo);

//routine
void	sleeping(t_philo *philo);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void *routine(void *arg);