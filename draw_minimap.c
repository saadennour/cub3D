/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:43:24 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/29 16:04:44 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_map_mlx_pixel_put(t_minimap *mini, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH / 5 || y < 0 || y >= WINDOW_HEIGHT / 4)
		return ;
	dst = mini->addr + (y * mini->line_length + x * (mini->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	innit_minimap(t_window *window, t_minimap *mini)
{
	mini->img = mlx_new_image(window->mlx, WINDOW_WIDTH / 5, WINDOW_HEIGHT / 4);
	mini->addr = mlx_get_data_addr(mini->img, &mini->bits_per_pixel,
			&mini->line_length, &mini->endian);
}

void	zoom_in(t_window *window, t_minimap *mini, char **map)
{
	while (map[mini->y_start] && mini->y_start <= mini->y_end)
	{
		mini->x = 0;
		mini->x_start = (window->y / 40) - (WINDOW_WIDTH / 5 / 2 / 40);
		while (mini->x_start <= mini->x_end)
		{
			if (map[mini->y_start][mini->x_start]
				&& map[mini->y_start][mini->x_start] == '1')
				draw_mini_square(mini->x * 40, mini->y * 40, mini, SKIN);
			else if (map[mini->y_start][mini->x_start]
				&& ft_strchr(map[mini->y_start][mini->x_start], "0NSWE"))
				draw_mini_square(mini->x * 40, mini->y * 40, mini, BEIGE);
			mini->x_start++;
			mini->x++;
		}
		mini->y_start++;
		mini->y++;
	}
}

void	draw_background(t_minimap *mini)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y <= WINDOW_HEIGHT / 4)
	{
		x = 0;
		while (x <= WINDOW_WIDTH / 5)
		{
			my_map_mlx_pixel_put(mini, x, y, SKIN);
			x++;
		}
		y++;
	}
}

void	draw_minimap(char **map, t_window *window)
{
	t_minimap	mini;

	innit_minimap(window, &mini);
	mini.player_size = TILE_SIZE;
	draw_background(&mini);
	minimap_cordinates(window, &mini);
	zoom_in(window, &mini, map);
	mini.player_size = 10;
	draw_mini_square(WINDOW_WIDTH / 5 / 2, WINDOW_HEIGHT / 4 / 2, &mini, RED);
	mlx_put_image_to_window(window->mlx, window->win, mini.img, 0, 0);
}
