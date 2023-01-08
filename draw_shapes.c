/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anass_elaoufi <anass_elaoufi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:00:48 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/08 17:33:14 by anass_elaou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

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
	int square_x;
	int square_y;
	int	temp_x;

	square_x = x + window->img_size;
	square_y = y + window->img_size;
	temp_x = x;
	while (y < square_y)
	{
		x = temp_x;
		while (x < square_x)
		{
			my_mlx_pixel_put(window->px, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(double x, double y, t_window *window, int color)
{
	//line(x + (window->img_size / 2), y + (window->img_size / 2), window, color);
	//drawing_rays(window);
	double start;

	start = window->rotation_angle - (FOV / 2);
	first_horizental_step(window, start);
	draw_square(x, y, window, color);
}
