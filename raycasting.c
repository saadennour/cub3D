/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:14:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/29 15:15:15 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	facing_down(t_window *window, double angle)
{
	window->ydirection = 1;
	if ((angle < M_PI && angle > 0))
		return (1);
	window->ydirection = -1;
	return (0);
}

int	facing_right(t_window *window, double angle)
{
	window->xdirection = 1;
	if (angle > M_PI / 2 && angle < 1.5 * M_PI)
		return (1);
	window->xdirection = -1;
	return (0);
}

void	first_horizental_step(t_window *window, double angle)
{
	(void)angle;
	window->ray.fh_y = floor(window->x / 40) * 40;
	if (facing_down(window, window->ray.start) == 1)
		window->ray.fh_y += 40;
	window->ray.fh_x = window->y + (window->x - window->ray.fh_y)
		/ tan(window->ray.start);
	if (window->ray.fh_x > 4000 || window->ray.fh_x < -4000)
		window->ray.fh_x = 9000;
	if (window->ray.fh_x < -4000)
		window->ray.fh_x = 9000 * -1;
}

void	horizental_steps(t_window *window, double angle)
{
	window->ray.horiz_y = 40 * window->ydirection;
	window->ray.horiz_x = window->ray.horiz_y / tan(angle);
	if (window->ray.horiz_x > 4000 || window->ray.horiz_x < -4000)
		window->ray.horiz_x = 9000;
	if (window->ray.horiz_x < -4000)
		window->ray.horiz_x = 9000 * -1;
	if ((window->ray.horiz_x < 0 && facing_right(window, angle))
		|| (window->ray.horiz_x > 0 && !facing_right(window, angle)))
		window->ray.horiz_x *= -1;
}

void	drawing_rays(t_window *window)
{
	window->ray.start = window->rotation_angle - (window->fov / 2);
	if (window->ray.start <= 0.0)
			window->ray.start += 2.0 * M_PI;
	if (window->ray.start >= 2.0 * M_PI)
			window->ray.start -= 2.0 * M_PI;
	first_horizental_step(window, window->ray.start);
}
