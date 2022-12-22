/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:50:34 by sfarhan           #+#    #+#             */
/*   Updated: 2022/12/23 00:07:22 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	start_game(t_config *config)
{
	int			w;
	int			h;
	t_window	window;
	
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, 40 * ft_strlen(config->data[6]), 40 * line_counter(&config->data[6]), "CUBE3D");
	window.wall = mlx_xpm_file_to_image(window.mlx, "wall.xpm", &w, &h);
	window.icon = mlx_xpm_file_to_image(window.mlx, "player.xpm", &w, &h);
	window.bg = mlx_xpm_file_to_image(window.mlx, "black.xpm", &w, &h);
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
	if (keycode == 0)
	{
		window->y -= 5;
		draw_square(window->y * 40, (window->x - 6) * 40, window, RED, 10);
	}
	else if (keycode == 1)
	{
		window->x += 5;
		draw_square(window->y * 40, (window->x - 6) * 40, window, RED, 10);
	}
	else if (keycode == 2)
	{
		window->y += 5;	
		draw_square(window->y * 40, (window->x - 6) * 40, window, RED, 10);
	}
	else if (keycode == 13)
	{
		window->x -= 5;
		draw_square(window->y * 40, (window->x - 6) * 40, window, RED, 10);
	}
	return (0);
}