/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:26:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/16 15:02:47 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

    xstep = 40 * window->xdirection;
    ystep = xstep * tan(window->ray.start);
    if ((ystep < 0 && facing_down(window, angle)) || (ystep > 0 && !facing_down(window, angle)))
		ystep *= -1;
    tempx = window->y;
	tempy = window->x;
    for (int i = 0; i < 3; i++)
	{
		draw_line(window, tempx, tempy, window->ray.fv_x, window->ray.fv_y, angle);
	 	tempx = window->ray.fv_x;
	 	tempy = window->ray.fv_y;
	 	window->ray.fv_x += xstep;
	 	window->ray.fv_y += ystep;
	}
}

void    wall_hit(t_window *window)
{
    while (find_wall(window, window->ray.fh_y, window->ray.fh_x) == 0)
}

// void    draw_rays(t_window *window)
// {
    
// }