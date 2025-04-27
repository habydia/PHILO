/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:14 by hadia             #+#    #+#             */
/*   Updated: 2025/04/23 20:37:48 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void init_philos(t_room room)
{
	t_philo *philos;
	int i;
	int j;

	philos = malloc(sizeof(t_philo) * room.number_of_philosopers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i++ < room.number_of_philosopers)
	{
		philos[i].id = i + 1;
		philos[i].room = &room;
		pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
	}
	room.forks = malloc(sizeof(pthread_mutex_t) * room.number_of_philosopers);
	if(!room.forks)
		return (NULL);
	j = 0;
	while(j++ < room.number_of_philosopers)
	{
		pthread_mutex_init(&room.forks[i], NULL);
	}

	return (room);
}

int main(int argc, char **argv)
{
	t_room room;

	if (argc != 2)
	{
		printf("%s", "usage: ./philo [nb_of_philo <= 5]");
		return (0);
	}
	room.number_of_philosopers = ft_atoi(argv[1]);
}
