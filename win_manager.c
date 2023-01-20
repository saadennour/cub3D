/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:50:34 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/18 15:23:47 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	start_game(t_config *config)
{
	t_window	window;
	
	window.mlx = mlx_init();
	window.height = 40 * line_counter(&config->data[6]);
	window.width = 40 * tallest_line(&config->data[6]);
	window.win = mlx_new_window(window.mlx, window.width ,window.height, "CUBE3D");
	window.map = config->data;
	window.rotation_speed = 2* M_PI / 60;
	window.rotation_angle = 0;
	window.track_rotation = 0;
	find_player(&window, config->data);
	minimap(config->data, &window);
	mlx_hook(window.win, 2, 1L << 0, key_hook, &window);
	mlx_hook(window.win, 17, 1L << 0, shut, &window);
	mlx_loop(window.mlx);
}

int	shut(t_window *window)
{
	mlx_destroy_window(window->mlx, window->win);
	exit (0);
}

void	round_angles(t_window *window)
{
	if (cos(window->rotation_angle) > 0)
		window->co = ceil(window->co);
	else
		window->co = floor(window->co);
	if (sin(window->rotation_angle) > 0)
		window->si = ceil(window->si);
	else
		window->si = floor(window->si);
	if ((cos(window->rotation_angle) > 0 && cos(window->rotation_angle) < 0.01)
		|| (cos(window->rotation_angle) < 0 && cos(window->rotation_angle) > -0.01))
		window->co = 0;
	if ((sin(window->rotation_angle) > 0 && sin(window->rotation_angle) < 0.01)
		|| (sin(window->rotation_angle) < 0 && sin(window->rotation_angle) > -0.01))
		window->si = 0;
}

int	key_hook(int keycode, t_window *window)
{
	int	x;
	int	y;

	x = window->x;
	y = window->y;
	if (keycode == 53)
		shut(window);
	mlx_destroy_image(window->mlx, window->img);
	if (keycode == RIGHT_ARROW)
	{
		window->track_rotation--;
		if (window->track_rotation <= -60)
			window->track_rotation = 0;
		window->rotation_angle -= 2 * M_PI / 180;
		if (window->ray.start <= 0.0)
			window->rotation_angle += 2.0 * M_PI;
		minimap(window->map, window);
	}
	if (keycode == LEFT_ARROW)
	{
		window->track_rotation++;
		if (window->track_rotation >= 60)
			window->track_rotation = 0;
		window->rotation_angle += 2 * M_PI / 180;
		if (window->ray.start >= 2.0 * M_PI)
			window->rotation_angle -= 2.0 * M_PI;
		minimap(window->map, window);	
	}
	if (keycode == A)
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
		minimap(window->map, window);
	}
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
		minimap(window->map, window);
	}
	if (keycode == D)
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
		minimap(window->map, window);
	}
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
		minimap(window->map, window);
	}
	else
		minimap(window->map, window);
	return (0);
}