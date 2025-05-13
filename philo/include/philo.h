/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:58 by hadia             #+#    #+#             */
/*   Updated: 2025/05/09 14:19:39 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define USAGE "usage: ./philo [nb_of_philo][time_to_die][to_eat][to_sleep]\n"

// data partagé
typedef struct s_room
{
	unsigned int    number_of_philosopers; // number of fork
	pthread_mutex_t *forks;
	pthread_mutex_t death_mutex;
	int				philo_dead;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
}					t_room;

// structure d'un philo
typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	time_t			last_meal_time;
	time_t			time_spent_eating;
	t_room			*room;
}					t_philo;

// utils
time_t				get_time_ms(void);
unsigned int		ft_atoi(const char *nptr);
void				print_status(t_philo *philo, char *status);
void				think(t_philo *philo);
int					check_death(t_philo *philo);

// init
void				init_room(t_room *room, char **argv);
void				init_logic(t_room *room, t_philo *philos);
void				simulation(t_room *room);

// routine
void				sleeping(t_philo *philo);
void				think(t_philo *philo);
void				eat(t_philo *philo);
void				*routine(void *arg);

#endif