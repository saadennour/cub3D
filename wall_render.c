/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:12:59 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/30 20:24:08 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	ray_dis(t_window *window, double x, double y)
{
	double	x1;
	double	y1;

	x1 = x - window->y;
	y1 = y - window->x;
	return (sqrt((x1 * x1) + (y1 * y1)));
}

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	get_pixel_color(t_window *window, double y_start, double y, int x)
{
	int			color;
	double		y_px;
	t_texture	*texture;

	texture = NULL;
	if (window->ray.v_or_h[x] == 1 && facing_right(window, window->ray.start))
		texture = window->east;
	if (window->ray.v_or_h[x] == 1 && !facing_right(window, window->ray.start))
		texture = window->west;
	if (window->ray.v_or_h[x] == 2 && facing_down(window, window->ray.start))
		texture = window->south;
	if (window->ray.v_or_h[x] == 2 && !facing_down(window, window->ray.start))
		texture = window->north;
	y_px = (texture->height / window->ray.wallheight) * (y_start - y);
	if (window->ray.v_or_h[x] == 1)
		color = get_pixel(texture, y_px, (int)window->ray.yrays[x]);
	else
		color = get_pixel(texture, y_px, (int)window->ray.xrays[x]);
	return (color);
}

void	draw_wall(t_window *window, int x)
{
	double		y_start;
	double		y_end;
	double		y;
	int			color;

	y_start = (WINDOW_HEIGHT / 2) - (window->ray.wallheight / 2);
	y_end = y_start + window->ray.wallheight;
	y = y_start;
	while (y_start < y_end)
	{
		color = get_pixel_color(window, y_start, y, x);
		my_mlx_pixel_put(window->px, x, y_start, color);
		y_start++;
	}
}

void	tree_d_drawing(t_window *window)
{
	int		i;
	double	ray_distance;

	i = 0;
	window->ray.start = window->rotation_angle - (window->fov / 2);
	while (i < NUMBER_OF_RAYS)
	{
		ray_distance = ray_dis(window, window->ray.xrays[i],
				window->ray.yrays[i])
			* cos(window->ray.start - window->rotation_angle);
		window->ray.wallheight = (TILE_SIZE / ray_distance)
			* window->ray.project_plane;
		draw_wall(window, i);
		i++;
		window->ray.start += window->fov / NUMBER_OF_RAYS;
	}
}
