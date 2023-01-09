/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:14:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/09 16:44:42 by aelaoufi         ###   ########.fr       */
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

void draw_line(t_window *window, int x, int y, int endX, int endY, double angle)
{
	(void)angle;
	double deltaX = endX - x;
	double deltaY = endY - y;
	// printf("deltax : %f | deltay : %f\n", deltaX, deltaY);
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	
	// printf("pix : %d\n", pixels);
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
	// printf("test\n");
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
	// printf("test1\n");
	first_x = window->y + (window->x - first_y) / tan(angle);
	ystep = 40;
	xstep = ystep / tan(angle);
	tempx = window->y + (window->img_size / 2);
	tempy = window->x + (window->img_size / 2);
	printf("xstep : %f  || firstx : %f\n", xstep, first_x);
	for (int i = 0; i < 2; i++)
	{
		draw_line(window, tempx, tempy, first_x, first_y, angle);
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
		if (start >= 3.14 && start <= 3.15)
			start += step;
		first_horizental_step(window, start);
		start += step;
		// printf("tan start : %f\n", tan(start));
	}
}