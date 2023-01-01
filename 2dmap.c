/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:36:12 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/01 17:08:03 by aelaoufi         ###   ########.fr       */
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

int	find_wall(t_window *window)
{
	int	x;
	int	y;

	y = 6;
	window->wall_x = 0;
	window->wall_y = 0;
	while (window->map[y])
	{
		x = 0;
		while(window->map[y][x])
		{
			if (ft_strchr(window->map[y][x], "1"))
			{
				window->wall_x = x * 40 + 15;
				window->wall_y = (y - 6) * 40 + 15;
			}
			if ((window->wall_x == window->x && window->wall_y == window->y)
				|| (window->wall_x == window->x + 10 && window->wall_y == window->y + 10))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
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