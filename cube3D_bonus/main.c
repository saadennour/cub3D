/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:03:34 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/30 19:22:10 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	main(int ac, char **av)
{
	int			fd;
	t_config	config;

	if (ac == 2)
	{
		check_extension(av[1], ".cub");
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			printf ("This map doesnt exist.\n");
			return (1);
		}
		config = get_config(fd);
		printf ("%d\n", config.colors->xceil);
		start_game(&config);
		system("leaks cub3D");
	}
	else
		printf ("Error : There is more than one argument\n");
	return (0);
}
