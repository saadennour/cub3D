/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:50:34 by sfarhan           #+#    #+#             */
/*   Updated: 2022/12/27 16:06:27 by aelaoufi         ###   ########.fr       */
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
	window.px->rotation_speed = 2* M_PI/180;
	window.px->rotation_angle = 0;
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
	if (keycode == 0)
	{
		window->px->rotation_angle += -1 * window->px->rotation_speed;
		window->y += sin(window->px->rotation_angle) * -7;
		//printf("rotation angle : %lf, y : %lf ON A -\n", window->px->rotation_angle, window->y);
		minimap(window->map, window);
	}
	else if (keycode == 1)
	{
		window->px->rotation_angle += 1 * window->px->rotation_speed;
		window->x += cos(window->px->rotation_angle) * 7;
		//printf("rotation angle : %lf, x : %lf\n ON W +", window->px->rotation_angle, window->x);
		minimap(window->map, window);
	}
	else if (keycode == 2)
	{
		window->px->rotation_angle += 1 * window->px->rotation_speed;
		window->y += sin(window->px->rotation_angle) * 7;
		//printf("rotation angle : %lf, y : %lf\n ON Q +", window->px->rotation_angle, window->y);
		minimap(window->map, window);
	}
	else if (keycode == 13)
	{
		window->px->rotation_angle += -1 * window->px->rotation_speed;
		window->x += cos(window->px->rotation_angle) * -7;
		minimap(window->map, window);
	}
	return (0);
}