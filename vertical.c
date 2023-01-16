/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:26:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/16 16:32:36 by aelaoufi         ###   ########.fr       */
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
    double	tempx;
	double	tempy;
	double	xstep;
	double	ystep;

    window->ray.vert_x = 40 * window->xdirection;
    window->ray.vert_y = window->ray.vert_x * tan(window->ray.start);
    if ((window->ray.vert_y < 0 && facing_down(window, angle)) || (window->ray.vert_y > 0 && !facing_down(window, angle)))
		window->ray.vert_y *= -1;
    tempx = window->y;
	tempy = window->x;
    // for (int i = 0; i < 3; i++)
	// {
	// 	draw_line(window, tempx, tempy, window->ray.fv_x, window->ray.fv_y, angle);
	//  	tempx = window->ray.fv_x;
	//  	tempy = window->ray.fv_y;
	//  	window->ray.fv_x += window->ray.vert_x;
	//  	window->ray.fv_y += window->ray.vert_y;
	// }
}

void    wall_hit(t_window *window)
{
    while (find_wall(window, window->ray.fh_y, window->ray.fh_x) == 0)
	{
		window->ray.fh_x += window->ray.horiz_x;
		window->ray.fh_y += window->ray.horiz_y;
	}
	while (find_wall(window, window->ray.fv_y, window->ray.fv_x) == 0)
	{
		window->ray.fv_x += window->ray.vert_x;
		window->ray.fv_y += window->ray.vert_y;
	}
	if (facing_down(window, window->ray.start))
		window->ray.yray = big(window->ray.fh_y, window->ray.fv_y);
	else
		window->ray.yray = small(window->ray.fh_y, window->ray.fv_y);
	if (facing_right(window, window->ray.start))
		window->ray.xray = small(window->ray.fh_x, window->ray.fv_x);
	else
		window->ray.xray = big(window->ray.fh_x, window->ray.fv_x);
}

void    draw_rays(t_window *window)
{
	double	step;
	
    window->ray.start = window->rotation_angle - (FOV / 2);
	window->ray.end = window->rotation_angle + (FOV / 2);
	step = 2 * M_PI / 180;
	if (window->ray.start <= 0.0)
			window->ray.start += 2.0 * M_PI;
	if (window->ray.start >= 2.0 * M_PI)
			window->ray.start -= 2.0 * M_PI;
	while (window->ray.start < window->ray.end)
	{
		first_horizental_step(window, window->ray.start);
		first_vertical_step(window);
		horizental_steps(window, window->ray.start);
		vertical_steps(window, window->ray.start);
		wall_hit(window);
		draw_line(window, window->y, window->x, window->ray.xray, window->ray.yray);
		window->ray.start += step;
	}
}