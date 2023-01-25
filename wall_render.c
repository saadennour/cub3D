/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:12:59 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/25 14:51:13 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

double	ray_dis(t_window *window, double x, double y)
{
	double x1;
	double y1;

	x1 = x - window->y;
	y1 = y - window->x; 
	return (sqrt((x1 * x1) + (y1 * y1)));
}

void	draw_wall(t_window *window, int x)
{
	double	y_start;
	double	y_end;
	double	y, y_px;
	t_texture	*texture;
	t_texture	*texture2;
	int	color;

	y_start = (WINDOW_HEIGHT / 2) - (window->ray.wallheight / 2);
	y_end = y_start + window->ray.wallheight;
	y = y_start;
	if (facing_down(window, window->ray.start))
		texture = window->south;
	else if (!facing_down(window, window->ray.start))
		texture = window->north;
	if (facing_right(window, window->ray.start))
		texture2 = window->west;
	else if (!facing_right(window, window->ray.start))
		texture2 = window->east;
	while (y_start < y_end)
	{
		y_px = (texture->height / window->ray.wallheight) * (y_start - y);
		if (window->ray.v_or_h[x] == 1)
			color = get_pixel(texture2, y_px, (int)window->ray.yrays[x]);
		else
			color = get_pixel(texture, y_px, (int)window->ray.xrays[x]);
		my_mlx_pixel_put(window->px, x, y_start, color);
	//	my_mlx_pixel_put(window->px, x + 1, y_start, BRICK);
		y_start++;
	}
}

void	tree_d_drawing(t_window *window)
{
	int		i;
	double	ray_distance;
	double	step;
	//li b3id kitrsem 9rib ou li 9rib kitrsem b3id
	i = 0;
    window->ray.start = window->rotation_angle - (FOV / 2);
	step = FOV / NUMBER_OF_RAYS;
	while (i < NUMBER_OF_RAYS)
	{
		ray_distance = ray_dis(window, window->ray.xrays[i], window->ray.yrays[i]) * cos(window->ray.start - window->rotation_angle);
		window->ray.wallheight = (TILE_SIZE / ray_distance) * window->ray.project_plane;
		draw_wall(window, i);
		window->ray.start += step;
		i++;
	}
}