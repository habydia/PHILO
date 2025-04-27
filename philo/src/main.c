/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:14 by hadia             #+#    #+#             */
/*   Updated: 2025/04/27 17:14:58 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


static void init_times(t_room *room)
{
	room->time_to_die = 800;    // Example values - adjust as needed
	room->time_to_eat = 200;
	room->time_to_sleep = 200;
	room->start_time = get_time_ms();
}

static void init_logic(t_room *room, t_philo *philos)
{
	unsigned int i;
	unsigned int j;
	 // Initialize mutexes
	 j = 0;
	 while (j < room->number_of_philosopers)
	 {
		 pthread_mutex_init(&room->forks[j], NULL);
		 j++;
	 }
	 init_times(room);
	 // Create philosopher threads
	 i = 0;
	 while (i < room->number_of_philosopers)
	 {
		 philos[i].id = i + 1;
		 philos[i].room = room;
		 pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
		 i++;
	 }
	 
	 // Keep main thread waiting for philosopher threads
	 i = 0;
	 while (i < room->number_of_philosopers)
	 {
		 pthread_join(philos[i].thread, NULL);
		 i++;
	 }
	 
}

static void init_room(t_room *room)
{
    t_philo *philos;

    // Allocate memory for philosophers
    philos = malloc(sizeof(t_philo) * room->number_of_philosopers);
    if (!philos)
    {
        // Handle error properly
        printf("Error: Failed to allocate memory for philosophers\n");
        exit(1);
    }
    
    // Allocate memory for forks BEFORE creating threads
    room->forks = malloc(sizeof(pthread_mutex_t) * room->number_of_philosopers);
    if (!room->forks)
    {
        printf("Error: Failed to allocate memory for forks\n");
        free(philos);
        exit(1);
    }
	room->start_time = get_time_ms();

	init_logic(room, philos);
	free(philos);

	// Destroy mutexes properly
    unsigned int j = 0;
    while (j < room->number_of_philosopers)
    {
        pthread_mutex_destroy(&room->forks[j]);
        j++;
    }
    
	free(room->forks);
}

int main(int argc, char **argv)
{
	t_room room;

	if (argc != 2)
	{
		printf("%s", "usage: ./philo [nb_of_philo <= 5]\n");
		return (0);
	}
	room.number_of_philosopers = ft_atoi(argv[1]);
	printf("number of philosophers: %d\n", room.number_of_philosopers);
	if (room.number_of_philosopers > 5)
	{
		printf("%s", "usage: ./philo [nb_of_philo <= 5]\n");
		return (0);
	}
	init_room(&room);
	return(0);
}
