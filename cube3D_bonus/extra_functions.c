/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:36:29 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/30 19:22:10 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	arrow_movement(int keycode, t_window *window)
{
	if (keycode == 53)
		shut(window);
	mlx_destroy_image(window->mlx, window->img);
	if (keycode == RIGHT_ARROW)
	{
		window->rotation_angle += 2 * M_PI / 180;
		if (window->ray.start >= 2.0 * M_PI)
			window->rotation_angle -= 2.0 * M_PI;
	}
	if (keycode == LEFT_ARROW)
	{
		window->rotation_angle -= 2 * M_PI / 180;
		if (window->ray.start <= 0.0)
			window->rotation_angle += 2.0 * M_PI;
	}
}

void	moving_left(int keycode, t_window *window)
{
	int	x;
	int	y;

	x = window->x;
	y = window->y;
	if (keycode == A)
	{
		window->si = (sin(window->rotation_angle) * 5);
		window->co = (cos(window->rotation_angle) * 5);
		round_angles(window);
		x -= window->co;
		y -= window->si;
		if (find_wall(window, x, y) == 1)
		{
			window->x = x;
			window->y = y;
		}
	}
}

void	moving_right(int keycode, t_window *window)
{
	int	x;
	int	y;

	x = window->x;
	y = window->y;
	if (keycode == D)
	{
		window->si = (sin(window->rotation_angle) * 5);
		window->co = (cos(window->rotation_angle) * 5);
		round_angles(window);
		x += window->co;
		y += window->si;
		if (find_wall(window, x, y) == 1)
		{
			window->x = x;
			window->y = y;
		}
	}
}

void	moving_up(int keycode, t_window *window)
{
	int	x;
	int	y;

	x = window->x;
	y = window->y;
	if (keycode == W)
	{
		window->si = (sin(window->rotation_angle) * 5);
		window->co = (cos(window->rotation_angle) * 5);
		round_angles(window);
		x += window->si;
		y -= window->co;
		if (find_wall(window, x, y) == 1)
		{
			window->x = x;
			window->y = y;
		}
	}
}

void	moving_down(int keycode, t_window *window)
{
	int	x;
	int	y;

	x = window->x;
	y = window->y;
	if (keycode == S)
	{
		window->si = (sin(window->rotation_angle) * 5);
		window->co = (cos(window->rotation_angle) * 5);
		round_angles(window);
		x -= window->si;
		y += window->co;
		if (find_wall(window, x, y) == 1)
		{
			window->x = x;
			window->y = y;
		}
	}
}
