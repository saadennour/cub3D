/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:00:48 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/12/27 17:18:34 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	line(int x, int y, double new_x, double new_y, t_data *data, int color)
{
	int dy, dx, incrE, incrNE, d,temp_x,temp_y;

	dx = new_x - x;
	dy = new_y - y;
	d = 2 * dy - dx;
	incrE = 2*dy;
	incrNE = 2*(dy - dx);
	temp_x = x;
	temp_y = y;
	my_mlx_pixel_put(data, temp_x, temp_y, color);
	while(temp_x < new_x)
	{
		if (d <= 0)
		{
			d += incrE;
			temp_x++;
		}
		else
		{
			d += incrNE;
			temp_x++;
			temp_y++;
		}
		my_mlx_pixel_put(data, temp_x, temp_y, color);
	} 
}

void	draw_line(int x, int y, t_data *data, int color, int size)
{
	(void)size;
	line(x ,y, data->line_x, data->line_y, data, color);
}

// float theta = 0;
// float h = 500;
// float k = 250;
// float r = 50;
// float step = 2*M_PI/300;
// while (theta < M_PI)
// {
// 	x = h + r*cos(theta);
// 	y = k - r*sin(theta);
// 	mlx_pixel_put(p->win_ptr, p->win_ptr, x, y, 0XF0F8FF);
// 	theta +=step;
// }
// void	draw_circle(int x, int y, t_data *data, int color)
// {
// 	double theta = 0;
// 	double h = 450;
// 	double k = 750;
// 	double r = 50;
// 	double step = 2*M_PI/300;
// 	while (theta < 2*M_PI)
// 	{
// 		x = h + r*cos(theta);
// 		y = k - r*sin(theta);
// 		my_mlx_pixel_put(data, x, y, color);
// 		theta +=step;
// 	}
// }

void	draw_circle(int x, int y, t_data *data, int color, int size)
{
	// double i, angle, x1, y1 = 0;

	// for(i = 0; i < 360; i += 0.1)
	// {
	// 	angle = i;
	// 	x1 = size * cos(angle * M_PI / 180);
	// 	y1 = size * sin(angle * M_PI / 180);
	// 	my_mlx_pixel_put(data, x + x1, y + y1, color);
	// }
	draw_line(x, y, data, color, size);
}

// if t goes from 0 to 2pi :

// x = sin(t) * r + center_x;
// y = cos(t) * r + center_y;
// x and y will be the circle-coordinates at given t with radius r and center coordinates (center_x, center_y)
void    draw_square(int x, int y, t_data *data, int color, int size)
{
	int square_x;
	int square_y;
	int	temp_x;

	square_x = x + size;
	square_y = y + size;
	temp_x = x;
	while (y < square_y)
	{
		x = temp_x;
		while (x < square_x)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void    draw_player(int x, int y, t_data *data, int color, int size)
{
	int square_x;
	int square_y;
	int	temp_x;
	int	temp_y;

	square_x = x + size;
	square_y = y + size;
	temp_x = x;
	temp_y = y;
	while (y < square_y)
	{
		x = temp_x;
		while (x < square_x)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
	draw_line(temp_x + (size / 2), temp_y + ((size -1) / 2), data, color, size + 5);
}
