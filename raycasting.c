/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anass_elaoufi <anass_elaoufi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:14:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/08 19:35:12 by anass_elaou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

void	signle_ray(double x, double y, double angle, t_window *window, int color)
{
	double deltaX = cos(angle);
	double deltaY = sin(angle);
	double tmpcos = deltaX;
	double tmpsin = deltaY;
	while (find_wall(window, y - 5, x - 5) == 1)
	{
		my_mlx_pixel_put(window->px, x, y, color);
		x += deltaX;
		y += deltaY;
		tmpcos++;
		tmpsin++;
	}
}

void draw_line(t_window *window, int x, int y, int endX, int endY)
{
	double deltaX = endX - x;
	double deltaY = endY - y;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = x;
	double pixelY = y;
	while (pixels)
	{
		my_mlx_pixel_put(window->px, pixelX, pixelY, YELLOW);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

void	first_horizental_step(t_window *window, double angle)
{
	double	first_y;
	double	first_x;
	double	tempx;
	double	tempy;
	double	xstep;
	double	ystep;
	
	first_y = floor(window->x / 40) * 40;
	first_x = window->y + (window->x - first_y) / tan(angle);
	ystep = 40;
	xstep = ystep / tan(angle);
	tempx = window->y;
	tempy = window->x;
	printf("test\n");
	while (find_wall(window, first_y - 5, first_x - 5) == 1)
	{
		draw_line(window, tempx, tempy, first_x, first_y);
		tempx = first_x;
		tempy = first_y;
		first_x += xstep;
		first_y -= ystep;
	}
	
}

void    drawing_rays(t_window *window)
{
	double	start;
	double	end;
	double	step;
	
	start = window->rotation_angle - (FOV / 2);
	end = window->rotation_angle + (FOV / 2);
	step = 2 * M_PI / 180;
	while (start < end)
	{
		signle_ray(window->y + (window->img_size / 2), window->x + (window->img_size / 2), start, window, YELLOW);
		start += step;
	}
}