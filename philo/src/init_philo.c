/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:41:09 by Hadia             #+#    #+#             */
/*   Updated: 2025/05/09 14:20:11 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_room(t_room *room, char **argv)
{
	room->number_of_philosopers = ft_atoi(argv[1]);
	room->time_to_die = ft_atoi(argv[2]);
	room->time_to_eat = ft_atoi(argv[3]);
	room->time_to_sleep = ft_atoi(argv[4]);
	room->start_time = get_time_ms();
	room->philo_dead = 0;
}

void	init_logic(t_room *room, t_philo *philos)
{
	unsigned int	i;
	unsigned int	j;

	pthread_mutex_init(&room->death_mutex, NULL);
	j = -1;
	while (j++ < room->number_of_philosopers)
		pthread_mutex_init(&room->forks[j], NULL);
	i = 0;
	while (i < room->number_of_philosopers)
	{
		philos[i].id = i + 1;
		philos[i].room = room;
		pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < room->number_of_philosopers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

/* Allocate memory for philosophers
 Handle error properly
 Allocate memory for forks BEFORE creating threads
 Destroy mutexes properly*/
void	simulation(t_room *room)
{
	t_philo			*philos;
	unsigned int	j;

	j = -1;
	philos = malloc(sizeof(t_philo) * room->number_of_philosopers);
	if (!philos)
	{
		printf("Error: Failed to allocate memory for philosophers\n");
		exit(1);
	}
	room->forks = malloc(sizeof(pthread_mutex_t) * room->number_of_philosopers);
	if (!room->forks)
	{
		printf("Error: Failed to allocate memory for forks\n");
		free(philos);
		exit(1);
	}
	init_logic(room, philos);
	free(philos);
	while (j++ < room->number_of_philosopers)
		pthread_mutex_destroy(&room->forks[j]);
	pthread_mutex_destroy(&room->death_mutex);
	free(room->forks);
}
