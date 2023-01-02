/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:50:34 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/02 12:39:22 by aelaoufi         ###   ########.fr       */
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
	window.rotation_speed = 2* M_PI / 60;
	window.rotation_angle = 0;
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
	if (window->rotation_angle == 4.712389)
	{
		window->rotation_angle = 3 * M_PI / 2;
		printf("round\n");
	}
}

int	key_hook(int keycode, t_window *window)
{
	if (keycode == 53)
		shut(window);
	mlx_destroy_image(window->mlx, window->img);
	if (keycode == RIGHT_ARROW)
	{
		window->rotation_angle += 2 * M_PI / 60;
		if (window->rotation_angle > 2.0 * M_PI)
			window->rotation_angle -= 2.0 * M_PI;
		round_angles(window);
		minimap(window->map, window);
	}
	if (keycode == LEFT_ARROW)
	{
		window->rotation_angle -= 2 * M_PI / 60;
		if (window->rotation_angle <= 0)
			window->rotation_angle += 2.0 * M_PI;
		round_angles(window);
		minimap(window->map, window);	
	}
	if (keycode == A)
	{
		printf("rotation angle : %f\n", window->rotation_angle);
		if (sin(window->rotation_angle) == 0.0)
		{
			window->x += 5;
			printf("test\n");
		}
		else if (cos(window->rotation_angle) == 0.0)
		{
			window->y += 5;
			printf("test\n");
		}
		else
		{
			window->x += (sin(window->rotation_angle) * 5);
			window->y -= (cos(window->rotation_angle) * 5);
		}
		minimap(window->map, window);
	}
	if (keycode == S)
	{
		printf("rotation angle : %f\n", window->rotation_angle);
		window->x -= (sin(window->rotation_angle) * 5);
		window->y -= (cos(window->rotation_angle) * 5);
		minimap(window->map, window);
	}
	if (keycode == D)
	{
		printf("rotation angle : %f\n", window->rotation_angle);
		if (sin(window->rotation_angle) == 0.0)
		{
			window->x -= 5;
			printf("test\n");
		}
		else if (cos(window->rotation_angle) == 0.0)
		{
			window->y -= 5;
			printf("test\n");
		}
		else
		{
			window->x -= (sin(window->rotation_angle) * 5);
			window->y += (cos(window->rotation_angle) * 5);
		}
		minimap(window->map, window);
	}
	if (keycode == W)
	{
		printf("rotation angle : %f\n", window->rotation_angle);
		window->x +=(sin(window->rotation_angle) * 5);
		window->y +=(cos(window->rotation_angle) * 5);
		minimap(window->map, window);
	}
	else
		minimap(window->map, window);
	return (0);
}