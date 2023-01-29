/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_innit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:55:43 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/29 16:04:57 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
