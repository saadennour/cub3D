/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anass_elaoufi <anass_elaoufi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:14:44 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/13 18:55:20 by anass_elaou      ###   ########.fr       */
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

int	facing_right(double angle)
{
	if (angle > M_PI / 2 && angle < 1.5 * M_PI)
		return (1);
	return (0);
}

void	init_ray(t_window *window, double angle)
{
	if ((tan(angle) < 0.1 && tan(angle) > 0) || (tan(angle) > -0.1 && tan(angle) < 0))
 		window->ray.start = 2 * M_PI / 180;
	window->ray.first_y = floor(window->x / 40) * 40;
	if (facing_down(window, window->ray.start) == 1)
		window->ray.first_y += 40;
	window->ray.first_x = window->y + (window->x - window->ray.first_y) / tan(window->ray.start);
}

void	first_horizental_step(t_window *window, double angle)
{
	double	tempx;
	double	tempy;
	double	xstep;
	double	ystep;
	
	// first_y = floor(window->x / 40) * 40;
	// if (facing_down(window, angle) == 1)
	// 	first_y += 40;
	printf("ray facing down : %d || ray facing right : %d\n", facing_down(window, window->ray.start), facing_right(window->ray.start));
	// first_x = window->y + (window->x - first_y) / tan(angle);
	ystep = 40 * window->ydirection;
	xstep = ystep / tan(angle);
	if ((xstep < 0 && facing_right(angle)) || (xstep > 0 && !facing_right(angle)))
		xstep *= -1;
	tempx = window->y;
	tempy = window->x;
	printf("firstx : %f\n", window->ray.first_x);
	printf("start : %f || rotation angle : %f\n", window->ray.start, window->rotation_angle);
	
	//printf("tan : %f\n", tan(angle));
	for (int i = 0; i < 2; i++)
	{
		draw_line(window, tempx, tempy, window->ray.first_x, window->ray.first_y, angle);
	 	tempx = window->ray.first_x;
	 	tempy = window->ray.first_y;
	 	window->ray.first_x += xstep;
		//if (tan(window->ray.start) >= 0 && tan(window->ray.start) >= 0)
	 		window->ray.first_y += ystep;
	}
	//printf("xdir : %d  || ydir : %d\n", window->xdirection, window->ydirection);
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
		init_ray(window, window->ray.start);
		//check_direction(window, start);
		first_horizental_step(window, window->ray.start);
		//check_direction(window, end);
		//first_horizental_step(window, end);
}