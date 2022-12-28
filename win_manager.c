/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anass_elaoufi <anass_elaoufi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:50:34 by sfarhan           #+#    #+#             */
/*   Updated: 2022/12/29 00:57:59 by anass_elaou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	start_game(t_config *config)
{
	t_window	window;
	
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, 40 * ft_strlen(config->data[6]), 40 * line_counter(&config->data[6]), "CUBE3D");
	window.map = config->data;
	find_player(&window, config->data);
	window.rotation_speed = 2* M_PI/ 60;
	window.rotation_angle = M_PI / 2;
	window.line_x = window.y + cos(window.rotation_angle) * 20;
	window.line_y = window.x + sin(window.rotation_angle) * 20;
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

int	key_hook(int keycode, t_window *window)
{
	if (keycode == 53)
		shut(window);
	mlx_destroy_image(window->mlx, window->img);
	if (keycode == A)
	{
		window->rotation_angle -= 0.2;
		if (window->rotation_angle < 0.0)
			window->rotation_angle += 2.0 * M_PI;
		//printf("A rotation angle : %lf\n", window->rotation_angle);
		window->line_x = window->y + (cos(window->rotation_angle) * 20);
		window->line_y = window->x + (sin(window->rotation_angle) * 20);
		// printf("A line x : %lf\n", window->line_x);
		// printf("A line y : %lf\n", window->line_y);
		minimap(window->map, window);
	}
	if (keycode == S)
	{
		window->y -= (sin(window->rotation_angle) * 20);
		window->x -= (cos(window->rotation_angle) * 20);
		window->line_x = window->y + (cos(window->rotation_angle) * 20);
		window->line_y = window->x + (sin(window->rotation_angle) * 20);
		minimap(window->map, window);
	}
	if (keycode == D)
	{
		window->rotation_angle += 0.2;
		if (window->rotation_angle > 2.0 * M_PI)
			window->rotation_angle -= 2.0 * M_PI;
		printf("D rotation angle : %lf\n", window->rotation_angle);
		window->line_x = window->y + (cos(window->rotation_angle) * 20);
		window->line_y = window->x + (sin(window->rotation_angle) * 20);
		// printf("D line x : %lf\n", window->line_x);
		// printf("D line y : %lf\n", window->line_y);
		minimap(window->map, window);
	}
	if (keycode == W)
	{
		window->y +=(sin(window->rotation_angle) * 20);
		window->x +=(cos(window->rotation_angle) * 20);
		window->line_x = window->y + (cos(window->rotation_angle) * 20);
		window->line_y = window->x + (sin(window->rotation_angle) * 20);
		minimap(window->map, window);
	}
	return (0);
}