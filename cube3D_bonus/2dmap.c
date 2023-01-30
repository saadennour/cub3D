/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:36:12 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/30 19:22:10 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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
	if (window->map[x][y] && (window->map[x][y] == '1'
		|| window->map[x2][y2] == '1'))
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
	window->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	window->px = malloc(sizeof(t_data));
	window->px->addr = mlx_get_data_addr(window->img,
			&window->px->bits_per_pixel,
			&window->px->line_length, &window->px->endian);
	window->player_size = TILE_SIZE;
	window->fov = 60 * M_PI / 180;
	window->ray.project_plane = (WINDOW_WIDTH / 2) / tan(window->fov / 2);
	draw_rays(window);
	draw_floor(window);
	draw_ceiling(window);
	tree_d_drawing(window);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
	draw_weapon(window);
	draw_minimap(&map[6], window);
}
