/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:00:48 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/12/30 21:04:28 by aelaoufi         ###   ########.fr       */
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
	double tmpcos = cos(window->rotation_angle);
	double tmpsin = sin(window->rotation_angle);

	//int pixels = (deltaX * deltaX) + (deltaY * deltaY);
	printf("A line x : %lf   x : %d\n", window->line_x, window->y);
	printf("A line y : %lf   y : %d\n", window->line_y, window->x);
	while (tmpcos < 20 && tmpsin < 20)
	{
		my_mlx_pixel_put(window->px, x, y, color);
		x += deltaX;
		y += deltaY;
		tmpcos++;
		tmpsin++;
		//--pixels;
	}
}


void	draw_line(double x, double y, t_window *window, int color)
{
	// printf("x: %d\ny: %d\n", x, y);
	// printf("line x: %lf\nline y: %lf\n", window->line_x, window->line_y);
	line(x, y, window, color);
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
	draw_square(x, y, window, color);
	draw_line(x + (window->img_size / 2), y + (window->img_size / 2), window, color);
}
