/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:26:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/16 21:13:26 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	big(double dis1, double dis2)
{
	if (dis1 > dis2)
		return (dis1);
	return (dis2);
}

double	small(double dis1, double dis2)
{
	if (dis1 > dis2)
		return (dis2);
	return (dis1);
}

void    first_vertical_step(t_window *window)
{
    window->ray.fv_x = floor(window->y / 40) * 40;
    if (facing_right(window, window->ray.start) == 1)
		window->ray.fv_x += 40;
    window->ray.fv_y = window->x + (window->y - window->ray.fv_x) * tan(window->ray.start);
}

void    vertical_steps(t_window *window, double angle)
{
    window->ray.vert_x = 40 * window->xdirection;
    window->ray.vert_y = window->ray.vert_x * tan(window->ray.start);
    if ((window->ray.vert_y < 0 && facing_down(window, angle)) || (window->ray.vert_y > 0 && !facing_down(window, angle)))
		window->ray.vert_y *= -1;
}

void	find_distance(t_window *window)
{
	double deltaX;
	double deltaY;

	deltaX = window->ray.fv_x - window->y;
	deltaY = window->ray.fv_y - window->x;
	window->ray.vert_distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX = window->ray.fh_x - window->y;
	deltaY = window->ray.fh_y - window->x;
	window->ray.horiz_distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

int	hor_map_limits(t_window *window)
{
	if (window->ray.fh_x >= window->width || window->ray.fh_x <= 0
		|| window->ray.fh_y >= window->height || window->ray.fh_y <= 0)
		return (1);
	return (0);
}

int	vert_map_limits(t_window *window)
{
	if (window->ray.fv_x >= window->width || window->ray.fv_x <= 0
		|| window->ray.fv_y >= window->height || window->ray.fv_y <= 0)
		return (1);
	return (0);
}

void    wall_hit(t_window *window)
{
    while (!hor_map_limits(window) && find_wall(window, window->ray.fh_y, window->ray.fh_x, -1))
	{
		window->ray.fh_x += window->ray.horiz_x;
		window->ray.fh_y += window->ray.horiz_y;
	}
	while (!vert_map_limits(window) && find_wall(window, window->ray.fv_y, window->ray.fv_x, -1))
	{
		window->ray.fv_x += window->ray.vert_x;
		window->ray.fv_y += window->ray.vert_y;
	}
	find_distance(window);
	if(window->ray.vert_distance < window->ray.horiz_distance)
	{
		window->ray.xray = window->ray.fv_x;
		window->ray.yray = window->ray.fv_y;
	}
	else
	{
		window->ray.xray = window->ray.fh_x;
		window->ray.yray = window->ray.fh_y;
	}
}

void    draw_rays(t_window *window)
{
	double	step;
	
    window->ray.start = window->rotation_angle - (FOV / 2);
	window->ray.end = window->rotation_angle + (FOV / 2);
	step = 2 * M_PI / 180;
	// if (window->ray.start <= 0.0)
	// 		window->ray.start += 2.0 * M_PI;
	// if (window->ray.start >= 2.0 * M_PI)
	// 		window->ray.start -= 2.0 * M_PI;
	
	while (window->ray.start < window->ray.end)
	{
		first_horizental_step(window, window->ray.start);
		first_vertical_step(window);
		horizental_steps(window, window->ray.start);
		vertical_steps(window, window->ray.start);
		wall_hit(window);
		draw_line(window, window->y, window->x, window->ray.xray, window->ray.yray);
		// printf("start : %f\n", window->ray.start);
		// printf("xray : %f\n", window->ray.xray);
		// printf("yray : %f\n", window->ray.fv_y);
		window->ray.start += step;
	}
}