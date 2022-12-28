/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anass_elaoufi <anass_elaoufi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:36:12 by sfarhan           #+#    #+#             */
/*   Updated: 2022/12/29 00:34:37 by anass_elaou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	find_player(t_window *window, char **map)
{
	int	x;
	int	y;

	x = 6;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (ft_strchr(map[x][y], "NSWE"))
			{
				window->x = (x - 6) * 40 + 15;
				window->y = y * 40 + 15;
			}
			y++;
		}
		x++;
	}
}

void	minimap(char **map, t_window *window)
{
	int	i;
	int	j;

	i = 6;
	window->img = mlx_new_image(window->mlx,  40 * ft_strlen(map[6]), 40 * line_counter(&map[6]));
	window->px = malloc(sizeof(t_data));
	window->px->addr = mlx_get_data_addr(window->img, &window->px->bits_per_pixel, &window->px->line_length, &window->px->endian);
	window->img_size = 40;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(j * 40, (i - 6) * 40, window, SKIN);
			else if (ft_strchr(map[i][j], "0NSWE"))
				draw_square(j * 40, (i - 6) * 40, window, BEIGE);
			j++;
		}
		i++;
	}
	window->img_size = 10;
	draw_player(window->y, window->x, window, RED);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}