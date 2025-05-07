/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:58 by hadia             #+#    #+#             */
/*   Updated: 2025/05/07 18:24:18 by Hadia            ###   ########.fr       */
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
    pthread_mutex_t death_mutex;
    int philo_dead;
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
    enum {false, true} alive;
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