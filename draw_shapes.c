/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:00:48 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/12/27 21:18:23 by aelaoufi         ###   ########.fr       */
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

void	draw_player(int x, int y, t_window *window, int color)
{
	draw_square(x, y, window, color);
	line(window->x, window->y, )
}
