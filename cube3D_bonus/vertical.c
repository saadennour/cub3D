/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:26:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/29 15:11:29 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	first_vertical_step(t_window *window)
{
	window->ray.fv_x = floor(window->y / 40) * 40;
	if (facing_right(window, window->ray.start) == 1)
		window->ray.fv_x += 40;
	window->ray.fv_y = window->x + (window->y - window->ray.fv_x)
		* tan(window->ray.start);
	if (window->ray.fv_y > 4000)
		window->ray.fv_y = 9000;
	if (window->ray.fv_y < -4000)
		window->ray.fv_y = 9000 * -1;
}

void	vertical_steps(t_window *window, double angle)
{
	window->ray.vert_x = 40 * window->xdirection;
	window->ray.vert_y = window->ray.vert_x * tan(window->ray.start);
	if (window->ray.vert_y > 4000 || window->ray.vert_y < -4000)
		window->ray.vert_y = 9000;
	if (window->ray.vert_y < -4000)
		window->ray.vert_y = 9000 * -1;
	if ((window->ray.vert_y < 0 && facing_down(window, angle))
		|| (window->ray.vert_y > 0 && !facing_down(window, angle)))
		window->ray.vert_y *= -1;
}

void	find_distance(t_window *window)
{
	double	deltax;
	double	deltay;

	deltax = window->ray.fv_x - window->y;
	deltay = window->ray.fv_y - window->x;
	window->ray.vert_distance = sqrt((deltax * deltax) + (deltay * deltay));
	deltax = window->ray.fh_x - window->y;
	deltay = window->ray.fh_y - window->x;
	window->ray.horiz_distance = sqrt((deltax * deltax) + (deltay * deltay));
}

void	draw_rays(t_window *window)
{
	double	step;
	int		i;

	i = 0;
	window->ray.start = window->rotation_angle - (window->fov / 2);
	window->ray.end = window->rotation_angle + (window->fov / 2);
	step = window->fov / NUMBER_OF_RAYS;
	window->ray.xrays = malloc(sizeof(double) * NUMBER_OF_RAYS);
	window->ray.yrays = malloc(sizeof(double) * NUMBER_OF_RAYS);
	window->ray.v_or_h = malloc(sizeof(int) * NUMBER_OF_RAYS);
	while (i < NUMBER_OF_RAYS)
	{
		first_horizental_step(window, window->ray.start);
		first_vertical_step(window);
		horizental_steps(window, window->ray.start);
		vertical_steps(window, window->ray.start);
		right_ray(window, i);
		window->ray.xrays[i] = window->ray.xray;
		window->ray.yrays[i] = window->ray.yray;
		window->ray.start += step;
		i++;
	}
}
