/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:50:34 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/24 16:50:46 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	start_game(t_config *config)
{
	t_window	window;
	int			w, h;
	
	window.mlx = mlx_init();
	window.height = 40 * line_counter(&config->data[6]);
	window.width = 40 * tallest_line(&config->data[6]);
	window.win = mlx_new_window(window.mlx, WINDOW_WIDTH , WINDOW_HEIGHT, "CUBE3D");
	window.map = config->data;
	window.rotation_angle = 0;
	window.north_img = mlx_xpm_file_to_image(window.mlx, "brick.xpm", &w, &h);
	window.north = malloc(sizeof(t_data));
	window.north->addr = mlx_get_data_addr(window.north_img, &window.north->bits_per_pixel, &window.north->line_length, &window.north->endian);
	printf ("addr = %p\n", window.north->addr);
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
		window->rotation_angle += 2 * M_PI / 180;
		if (window->ray.start >= 2.0 * M_PI)
			window->rotation_angle -= 2.0 * M_PI;
		minimap(window->map, window);
	}
	if (keycode == LEFT_ARROW)
	{
		window->rotation_angle -= 2 * M_PI / 180;
		if (window->ray.start <= 0.0)
			window->rotation_angle += 2.0 * M_PI;
		minimap(window->map, window);	
	}
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
		x += window->co;
		y += window->si;
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