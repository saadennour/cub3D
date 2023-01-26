/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:12:59 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/26 21:09:53 by aelaoufi         ###   ########.fr       */
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

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	draw_wall(t_window *window, int x)
{
	double	y_start;
	double	y_end;
	double	y, y_px;
	t_texture	*texture = NULL;
	// t_texture	*texture2;
	int	color;

	y_start = (WINDOW_HEIGHT / 2) - (window->ray.wallheight / 2);
	y_end = y_start + window->ray.wallheight;
	y = y_start;
	// if (facing_down(window, window->ray.start))
	// 	texture = window->south;
	// else
	// 	texture = window->north;
	// if (facing_right(window, window->ray.start))
	// 	texture2 = window->east;
	// else
	// 	texture2 = window->west;
	while (y_start < y_end)
	{
		// y_px = (texture->height / window->ray.wallheight) * (y_start - y);
		// printf ("salam\n");
		if (window->ray.v_or_h[x] == 1 && facing_right(window, window->ray.start))
		{
			texture = window->east;
			y_px = (texture->height / window->ray.wallheight) * (y_start - y);
			color = get_pixel(texture, y_px, (int)window->ray.yrays[x]);
		}
		if (window->ray.v_or_h[x] == 1 && !facing_right(window, window->ray.start))
		{
			texture = window->west;
			y_px = (texture->height / window->ray.wallheight) * (y_start - y);
			color = get_pixel(texture, y_px, (int)window->ray.yrays[x]);
		}
		if (window->ray.v_or_h[x] == 2 && facing_down(window, window->ray.start))
		{
			texture = window->south;
			y_px = (texture->height / window->ray.wallheight) * (y_start - y);
			color = get_pixel(texture, y_px, (int)window->ray.xrays[x]);
		}
		if (window->ray.v_or_h[x] == 2 && !facing_down(window, window->ray.start))
		{
			texture = window->north;
			y_px = (texture->height / window->ray.wallheight) * (y_start - y);
			color = get_pixel(texture, y_px, (int)window->ray.xrays[x]);
		}
		my_mlx_pixel_put(window->px, x, y_start, color);
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
	while (i < NUMBER_OF_RAYS)
	{
		ray_distance = ray_dis(window, window->ray.xrays[i], window->ray.yrays[i]) * cos(window->ray.start - window->rotation_angle);
		window->ray.wallheight = (TILE_SIZE / ray_distance) * window->ray.project_plane;
		draw_wall(window, i);
		window->ray.start += step;
		i++;
		window->ray.start += FOV / NUMBER_OF_RAYS;
	}
}