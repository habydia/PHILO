/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:14 by hadia             #+#    #+#             */
/*   Updated: 2025/05/09 14:05:53 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_room	room;

	if (argc != 5)
	{
		printf(USAGE);
		return (0);
	}
	init_room(&room, argv);
	simulation(&room);
	return (0);
}
