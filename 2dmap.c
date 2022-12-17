/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:36:12 by sfarhan           #+#    #+#             */
/*   Updated: 2022/12/17 23:51:11 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	minimap(char **map, t_window *window)
{
	int	i;
	int	j;

	i = 6;
	printf ("lenght : %d\n", ft_strlen(map[6]));
	printf ("height : %d\n", line_counter(&map[6]));
	while (map[i])
	{
		j = 0;
		printf ("%s\n", map[i]);
		while (map[i][j])
		{
			if (map[i][j] == '1')
				mlx_put_image_to_window(window->mlx, window->win, window->wall, j * 80, (i - 6) * 80);
			else if (ft_strchr(map[i][j], "NSWE"))
				mlx_put_image_to_window(window->mlx, window->win, window->icon, j * 80, (i - 6) * 80);
			j++;
		}
		i++;
	}
}