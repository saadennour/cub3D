/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:36:12 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/27 19:46:56 by sfarhan          ###   ########.fr       */
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
				if (map[x][y] == 'N')
					window->rotation_angle = 3 * M_PI / 2;
				else if (map[x][y] == 'S')
					window->rotation_angle = M_PI / 2;
				else if (map[x][y] == 'W')
					window->rotation_angle = 0;
				window->x = (x - 6) * 40 + 15;
				window->y = y * 40 + 15;
			}
			y++;
		}
		x++;
	}
}

int	find_wall(t_window *window, int i, int j)
{
	int	x;
	int	y;
	int	x2;
	int	y2;

	x = (i - 5) / 40 + 6;
	y = (j - 5) / 40;
	x2 = i / 40 + 6;
	y2 = j / 40;
	if (window->map[x][y] && (window->map[x][y] == '1' || window->map[x2][y2] == '1'))
		return (0);
	else
		return (1);
	return (0);
}

int	find_wall_horiz(t_window *window, int i, int j)
{
	int	x;
	int	y;

	x = (i - 2) / 40 + 6;
	if (facing_down(window, window->ray.start))
		x = (i + 39) / 40 + 6;
	y = j / 40;
	if (!facing_right(window, window->ray.start))
		y = j / 40;
	// should truncate spaces in the end of each line in the map
	if (window->map[x][y] && window->map[x][y] == '1')
		return (0);
	return (1);
}

int	find_wall_vert(t_window *window, int i, int j)
{
	int	x;
	int	y;

	x = i / 40 + 6;
	y = j / 40;
	if (!facing_right(window, window->ray.start))
		y = (j - 40) / 40;
	if (window->map[x][y] && window->map[x][y] == '1')
		return (0);
	else
		return (1);
	return (0);
}

void	minimap(char **map, t_window *window)
{
	// int	i;
	// int	j;

	// i = 6;
	window->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	window->px = malloc(sizeof(t_data));
	window->px->addr = mlx_get_data_addr(window->img, &window->px->bits_per_pixel, &window->px->line_length, &window->px->endian);
	window->player_size = TILE_SIZE;
	window->ray.project_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	draw_rays(window);
	draw_floor(window);
	draw_ceiling(window);
	tree_d_drawing(window);
	// while (map[i])
	// {
	// 	j = 0;
	// 	while (map[i][j])
	// 	{
	// 		if (map[i][j] == '1')
	// 			draw_square(SCALE_DOWN * (j * TILE_SIZE), SCALE_DOWN * (i - 6) * TILE_SIZE, window, SKIN);
	// 		else if (ft_strchr(map[i][j], "0NSWE"))
	// 			draw_square(SCALE_DOWN * (j * TILE_SIZE), SCALE_DOWN * (i - 6) * TILE_SIZE, window, BEIGE);
	// 		j++;
	// 	}
	// 	i++;
	// }
	window->player_size = SCALE_DOWN * 10;
	//draw_player(window->y, window->x, window, RED);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
	draw_minimap(map, window);
}