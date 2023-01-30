/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_innit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:55:43 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/30 19:22:10 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	draw_mini_square(int x, int y, t_minimap *mini, int color)
{
	int	square_x;
	int	square_y;
	int	temp_x;

	square_x = (x + mini->player_size);
	square_y = (y + mini->player_size);
	temp_x = x;
	while (y <= square_y)
	{
		x = temp_x;
		while (x <= square_x)
		{
			my_map_mlx_pixel_put(mini, x, y, color);
			x++;
		}
		y++;
	}
}

void	minimap_cordinates(t_window *window, t_minimap *mini)
{
	mini->x_start = (window->y / 40) - (WINDOW_WIDTH / 5 / 2 / 40);
	mini->x_end = ((window->y / 40) + (WINDOW_WIDTH / 5 / 2 / 40));
	mini->y_start = ((window->x / 40) - (WINDOW_HEIGHT / 4 / 2 / 40));
	mini->y_end = ((window->x / 40) + (WINDOW_HEIGHT / 4 / 2 / 40));
	mini->y = 0;
}

void	draw_weapon(t_window *window)
{
	int	x;
	int	y;

	x = WINDOW_WIDTH - (WINDOW_WIDTH / 2.7);
	y = WINDOW_HEIGHT - (WINDOW_HEIGHT / 2.6);
	mlx_put_image_to_window(window->mlx, window->win,
		window->weapon->img, x, y);
}
