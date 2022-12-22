/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:00:48 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/12/23 00:04:17 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void    draw_square(int x, int y, t_window *p, int color, int size)
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
			mlx_pixel_put(p->mlx, p->win, x, y, color);
			x++;
		}
		y++;
	}
}