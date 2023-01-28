/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:03:34 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/28 21:54:04 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int ac, char **av)
{
	int	fd;
	int	i=0,j=0;
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
		printf ("%s\n", config.idpaths->north_path);
		printf ("%s\n", config.idpaths->south_path);
		printf ("%s\n", config.idpaths->east_path);
		printf ("%s\n", config.idpaths->west_path);
		while (i < 3)
			printf ("%d|\n", config.colors->floor[i++]);
		while (j < 3)
			printf ("%d|\n", config.colors->ceiling[j++]);
		i = 0;
		while (config.data[i])
		{
			printf ("%s|\n", config.data[i]);
			i++;
		}
		// system("leaks cub3D");
		start_game(&config);
	}
	else
		printf ("Error : There is more than one argument\n");
	return (0);
}
