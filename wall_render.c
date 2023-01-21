/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:12:59 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/21 14:32:58 by aelaoufi         ###   ########.fr       */
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
	double y_end;

	//x = x * 2;
	y_start = (WINDOW_HEIGHT / 2) - (window->ray.wallheight / 2);
	y_end = y_start + window->ray.wallheight;
	//printf y_start and wall height to see why it doesnt draw the strips
	//printf("y start : %d || wall height : %f\n", y_start, window->ray.wallheight);
	while (y_start < y_end)
	{
		my_mlx_pixel_put(window->px, x, y_start, BRICK);
	//	my_mlx_pixel_put(window->px, x + 1, y_start, BRICK);
		y_start++;
		//printf("test\n");
	}
}

void	tree_d_drawing(t_window *window)
{
	int		i;
	double	ray_distance;
	//li b3id kitrsem 9rib ou li 9rib kitrsem b3id
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		ray_distance = ray_dis(window, window->ray.xrays[i], window->ray.yrays[i]) * cos(window->ray.start - window->rotation_angle);
		window->ray.wallheight = (TILE_SIZE / ray_distance) * window->ray.project_plane;
		draw_wall(window, i);
		i++;
	}
}