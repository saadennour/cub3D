/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:50:34 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/03 21:47:44 by sfarhan          ###   ########.fr       */
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
	window.track_rotation = 0;
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
}

int	key_hook(int keycode, t_window *window)
{	
	if (keycode == 53)
		shut(window);
	mlx_destroy_image(window->mlx, window->img);
	if (keycode == RIGHT_ARROW)
	{
		window->track_rotation++;
		if (window->track_rotation >= 60)
			window->track_rotation = 0;
		window->rotation_angle += 2 * M_PI / 60;
		if (window->rotation_angle > 2.0 * M_PI)
		{	window->rotation_angle -= 2.0 * M_PI;
			// printf("enter\n");
		}
		minimap(window->map, window);
	}
	if (keycode == LEFT_ARROW)
	{
		window->track_rotation--;
		if (window->track_rotation <= -60)
			window->track_rotation = 0;
		window->rotation_angle -= 2 * M_PI / 60;
		if (window->rotation_angle < 0)
		{	window->rotation_angle += 2.0 * M_PI;
			// printf("enter\n");
		}
		minimap(window->map, window);	
	}
	if (keycode == A)
	{
		//printf("tracker : %d\n", window->track_rotation);
		window->si = (sin(window->rotation_angle) * 5);
		window->co = (cos(window->rotation_angle) * 5);
		round_angles(window);
		if (window->track_rotation == 0 || window->track_rotation == 30 || window->track_rotation == -30)
			window->x += 5;
		else if (window->track_rotation == 15 || window->track_rotation == -15 || window->track_rotation == 45 || window->track_rotation == -45)
			window->y -= 5;
		else
		{
			window->x -= window->co;
			window->y += window->si;
		}
		minimap(window->map, window);
	}
	if (keycode == S)
	{
		window->si = (sin(window->rotation_angle) * 5);
		window->co = (cos(window->rotation_angle) * 5);
		round_angles(window);
		// printf("S cos : %f\n", cos(window->rotation_angle));
		// printf("S sin : %f\n", sin(window->rotation_angle));
		
		// printf("tracker : %d\n", window->track_rotation);
		if (window->track_rotation == 30 || window->track_rotation == -30)
			window->y += 5;
		else if (window->track_rotation == 15 || window->track_rotation == -15)
			window->x += 5;
		else if (window->track_rotation == 45 || window->track_rotation == -45)
			window->x -= 5;
		else if (window->track_rotation == 0)
			window->y -= 5;
		else
		{
			window->x -= window->si;
			window->y -= window->co;
		}
		minimap(window->map, window);
	}
	if (keycode == D)
	{
	//	printf("tracker : %d\n", window->track_rotation);
		window->si = (sin(window->rotation_angle) * 5);
		window->co = (cos(window->rotation_angle) * 5);
		round_angles(window);
		if (window->track_rotation == 0 || window->track_rotation == 30 || window->track_rotation == -30)
			window->x -= 5;
		else if (window->track_rotation == 15 || window->track_rotation == -15 || window->track_rotation == 45 || window->track_rotation == -45)
			window->y += 5;
		else
		{
			window->x += window->co;
			window->y -= window->si;
		}
		minimap(window->map, window);
	}
	if (keycode == W)
	{
		if (find_wall(window) == 1)
		{
			window->si = (sin(window->rotation_angle) * 5);
			window->co = (cos(window->rotation_angle) * 5);
			round_angles(window);
			// printf("tracker : %d\n", window->track_rotation);
			// printf("W sin : %f\n", window->si);
			// printf("W cos : %f\n", window->co);
			//30 and -30 y--; www
			if (window->track_rotation == 30 || window->track_rotation == -30)
				window->y -= 5;
			else if (window->track_rotation == 15 || window->track_rotation == -15)
				window->x -= 5;
			else if (window->track_rotation == 45 || window->track_rotation == -45)
				window->x += 5;
			else if (window->track_rotation == 0)
				window->y += 5;
			else
			{
				window->x += window->si;
				window->y += window->co;
			}
		}
		minimap(window->map, window);
	}
	else
		minimap(window->map, window);
	return (0);
}