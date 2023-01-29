/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_extra_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:00:35 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/29 15:05:55 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	vert_map_limits(t_window *window)
{
	if (window->ray.fv_x >= window->width || window->ray.fv_x <= 0
		|| window->ray.fv_y >= window->height || window->ray.fv_y <= 0)
		return (1);
	return (0);
}

int	hor_map_limits(t_window *window)
{
	if (window->ray.fh_x >= window->width || window->ray.fh_x <= 0
		|| window->ray.fh_y >= window->height || window->ray.fh_y <= 0)
		return (1);
	return (0);
}

void	wall_hit(t_window *window)
{
	while (!hor_map_limits(window)
		&& find_wall_horiz(window, window->ray.fh_y, window->ray.fh_x))
	{
		window->ray.fh_x += window->ray.horiz_x;
		window->ray.fh_y += window->ray.horiz_y;
	}
	while (!vert_map_limits(window)
		&& find_wall_vert(window, window->ray.fv_y, window->ray.fv_x))
	{
		window->ray.fv_x += window->ray.vert_x;
		window->ray.fv_y += window->ray.vert_y;
	}
	find_distance(window);
}

void	right_ray(t_window *window, int i)
{
	wall_hit(window);
	if (window->ray.vert_distance < window->ray.horiz_distance)
	{
		window->ray.xray = window->ray.fv_x;
		window->ray.yray = window->ray.fv_y;
		window->ray.v_or_h[i] = 1;
	}
	else
	{
		window->ray.xray = window->ray.fh_x;
		window->ray.yray = window->ray.fh_y;
		window->ray.v_or_h[i] = 2;
	}
	if (window->ray.vert_distance == window->ray.horiz_distance)
	{
		window->ray.xray = trunc(window->ray.xray);
		window->ray.yray = trunc(window->ray.yray);
	}
}
