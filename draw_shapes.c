/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:00:48 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/28 16:44:06 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	line(double x, double y, t_window *window, int color)
{
	double deltaX = cos(window->rotation_angle);
	double deltaY = sin(window->rotation_angle);
	double tmpcos = deltaX;
	double tmpsin = deltaY;
	while (tmpcos < 20 && tmpsin < 20)
	{
		my_mlx_pixel_put(window->px, x, y, color);
		x += deltaX;
		y += deltaY;
		tmpcos++;
		tmpsin++;
	}
}

void	draw_square(int x, int y, t_window *window, int color)
{
	int	square_x;
	int	square_y;
	int	temp_x;

	square_x = (x + window->player_size);
	square_y = (y + window->player_size);
	temp_x = x;
	while (y <= square_y)
	{
		x = temp_x;
		while (x <= square_x)
		{
			my_mlx_pixel_put(window->px, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_ceiling(t_window *window)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(window->px, x, y, window->ceil);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_window *window)
{
	int x;
	int y;

	y = WINDOW_HEIGHT / 2;
	x = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(window->px, x, y, window->floor);
			x++;
		}
		y++;
	}
}

void	draw_player(double x, double y, t_window *window, int color)
{
	(void)x;
	(void)y;
	(void)color;
	draw_square(SCALE_DOWN * (x - 5), SCALE_DOWN * (y - 5), window, color);
}
