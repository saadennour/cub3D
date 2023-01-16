/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:14:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/16 21:16:01 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

void	signle_ray(double x, double y, double angle, t_window *window, int color)
{
	double deltaX = cos(angle);
	double deltaY = sin(angle);
	double tmpcos = deltaX;
	double tmpsin = deltaY;
	while (find_wall(window, y - 5, x - 5, 5) == 1)
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
		if (pixelX >= window->width || pixelY >= window->height || pixelX <= 0 || pixelY <= 0)
			break ;
		my_mlx_pixel_put(window->px, pixelX, pixelY, YELLOW);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	// printf("test\n");
}

void	check_direction(t_window *window, double angle)
{
	if (angle > 1.5 * M_PI && angle < 2 * M_PI)
	{
		window->ydirection = -1;//facing up
		window->xdirection = -1;
	}
	if (angle > 0 && angle < M_PI / 2)
	{
		window->ydirection = 1;//facing up
		window->xdirection = -1;
	}
	if (angle > M_PI / 2 && angle < M_PI)
	{
		window->ydirection = 1;//facing down
		window->xdirection = 1;
	}
	if (angle > M_PI && angle < 1.5 * M_PI)
	{
		window->ydirection = 1;//facing down
		window->xdirection = -1;
	}
}

int	facing_down(t_window *window, double angle)
{
	window->ydirection = 1;
	if ((angle < M_PI && angle >= 0) || (angle > 6.26 && angle < 6.29))
		return (1);
	window->ydirection = -1;
	return (0);
}

int	facing_right(t_window *window, double angle)
{
	window->xdirection = 1;
	if (angle > M_PI / 2 && angle < 1.5 * M_PI)
		return (1);
	window->xdirection = -1;
	return (0);
}

void	first_horizental_step(t_window *window, double angle)
{
	(void)angle;
	window->ray.fh_y = floor(window->x / 40) * 40;
	if (facing_down(window, window->ray.start) == 1)
		window->ray.fh_y += 40;
	window->ray.fh_x = window->y + (window->x - window->ray.fh_y) / tan(window->ray.start);
}

void	horizental_steps(t_window *window, double angle)
{
	window->ray.horiz_y = 40 * window->ydirection;
	window->ray.horiz_x = window->ray.horiz_y / tan(angle);
	if ((window->ray.horiz_x < 0 && facing_right(window, angle)) || (window->ray.horiz_x > 0 && !facing_right(window, angle)))
		window->ray.horiz_x *= -1;
	// for (int i = 0; i < 9; i++)
	// {
	// 	draw_line(window, tempx, tempy, window->ray.fh_x, window->ray.fh_y, angle);
	//  	tempx = window->ray.fh_x;
	//  	tempy = window->ray.fh_y;
	//  	window->ray.fh_x += window->ray.horiz_x;
	//  	window->ray.fh_y += window->ray.horiz_y;
	// }
}

void    drawing_rays(t_window *window)
{
	// double	step;
	
	window->ray.start = window->rotation_angle - (FOV / 2);
	// window->ray.end = window->rotation_angle + (FOV / 2);
	// step = 2 * M_PI / 180;
	// while (window->ray.start <window->ray.end)
	// {
	// 	init_ray(window);
	// 	if (window->ray.start >= 3.14 && window->ray.start <= 3.15)
	// 		window->ray.start += step;
	// 	first_horizental_step(window, window->ray.start);
	// 	window->ray.start += step;
	// }
	if (window->ray.start <= 0.0)
			window->ray.start += 2.0 * M_PI;
	if (window->ray.start >= 2.0 * M_PI)
			window->ray.start -= 2.0 * M_PI;
		first_horizental_step(window, window->ray.start);
		// first_vertical_step(window);
		// vertical_steps(window, window->ray.start);

}