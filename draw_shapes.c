/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anass_elaoufi <anass_elaoufi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:00:48 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/12/28 22:36:56 by anass_elaou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void	line(double x, double y, double new_x, double new_y, t_data *data, int color)
// {
// 	double dy, dx, incrE, incrNE, d,temp_x,temp_y;

// 	dx = new_x - x;
// 	dy = new_y - y;
// 	d = 2 * dy - dx;
// 	incrE = 2*dy;
// 	incrNE = 2*(dy - dx);
// 	temp_x = x;
// 	temp_y = y;
// 	my_mlx_pixel_put(data, temp_x, temp_y, color);
// 	while(temp_x < new_x)
// 	{
// 		my_mlx_pixel_put(data, temp_x, temp_y, color);
// 		if (d <= 0)
// 		{
// 			d += incrE;
// 			temp_x++;
// 		}
// 		else
// 		{
// 			d += incrNE;
// 			temp_x++;
// 			temp_y++;
// 		}
// 	} 
// }

void	line(double x, double y, double new_x, double new_y, t_data *data, int color)
{
	// Calculate "deltas" of the line (difference between two ending points)
    double dx = new_x - x;
    double dy = new_y - y;
    // Calculate the line equation based on deltas
    double d = (2 * dy) - dx;
    double temp_y = y;
    // Draw the line based on arguments provided
    for (double temp_x = x; temp_x < new_x; temp_x++)
    {
        // Place pixel on the raster display
        my_mlx_pixel_put(data, temp_x, temp_y, color);
        if (d >= 0)
        {
            temp_y = temp_y + 1;
            d = d - 2 * dx;
        }
        d = d + 2 * dy;
    }
}


void	draw_line(double x, double y, t_window *window, int color)
{
	// printf("x: %d\ny: %d\n", x, y);
	// printf("line x: %lf\nline y: %lf\n", window->line_x, window->line_y);
	line(x, y, window->line_x, window->line_y, window->px, color);
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
	draw_line(x + (window->img_size / 2), y + ((window->img_size - 1) / 2), window, color);
}
