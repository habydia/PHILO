/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvby <hvby@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:58 by hadia             #+#    #+#             */
/*   Updated: 2025/04/23 19:37:23 by hvby             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
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
} t_room;


//structure d'un philo
typedef struct s_philo
{
    pthread_t thread;
    unsigned int id;
    t_room *room;
}   t_philo;