/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:36:12 by sfarhan           #+#    #+#             */
/*   Updated: 2022/12/20 17:21:12 by sfarhan          ###   ########.fr       */
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
				mlx_put_image_to_window(window->mlx, window->win, window->wall, j * 40, (i - 6) * 40);
			else if (ft_strchr(map[i][j], "0 "))
				mlx_put_image_to_window(window->mlx, window->win, window->bg, j * 40, (i - 6) * 40);
			else if (ft_strchr(map[i][j], "NSWE"))
			{
				mlx_put_image_to_window(window->mlx, window->win, window->icon, j * 40, (i - 6) * 40);
				window->y = j * 40;
				window->x = (i - 6) * 40;
			}
			j++;
		}
		i++;
	}
}