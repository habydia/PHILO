/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:14 by hadia             #+#    #+#             */
/*   Updated: 2025/05/07 23:18:33 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// static void init_times(t_room *room, char *time)
// {
// 	room->time_to_die = ft_atoi(time);    // Example values - adjust as needed
// 	room->time_to_eat = ft_atoi(time);
// 	room->time_to_sleep = ft_atoi(time);
// 	room->start_time = get_time_ms();
// }

// Initialize mutexes
// Create philosopher threads
// Keep main thread waiting for philosopher threads
static void init_logic(t_room *room, t_philo *philos)
{
	unsigned int i;
	unsigned int j;

	pthread_mutex_init(&room->death_mutex, NULL);
	 j = -1;
	 while (j++ < room->number_of_philosopers)
		 pthread_mutex_init(&room->forks[j], NULL);
	//  init_times(room);
	 i = 0;
	 while (i < room->number_of_philosopers)
	 {
		 philos[i].id = i + 1;
		 philos[i].room = room;
		 philos[i].alive = true;
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

// Allocate memory for philosophers
// Handle error properly
// Allocate memory for forks BEFORE creating threads
// Destroy mutexes properly
static void init_room(t_room *room)
{
    t_philo *philos; 
	unsigned int j;
	
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
	room->start_time = get_time_ms();
	room->philo_dead = 0;
	init_logic(room, philos);
	free(philos);
    while (j++ < room->number_of_philosopers)
        pthread_mutex_destroy(&room->forks[j]);
    pthread_mutex_destroy(&room->death_mutex);
	free(room->forks);
}

int main(int argc, char **argv)
{
	t_room room;

	if (argc != 5)
	{
		printf("%s", "usage: ./philo [nb_of_philo <= 5]\n");
		return (0);
	}
	room.number_of_philosopers = ft_atoi(argv[1]);
	room.time_to_die = ft_atoi(argv[2]);   
	room.time_to_eat = ft_atoi(argv[3]);
	room.time_to_sleep = ft_atoi(argv[4]);
	room.start_time = get_time_ms();

	printf("number of philosophers: %d\n", room.number_of_philosopers);
	if (room.number_of_philosopers > 5)
	{
		printf("%s", "usage: ./philo [nb_of_philo <= 5]\n");
		return (0);
	}
	init_room(&room);
	return(0);
}
