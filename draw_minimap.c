/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:43:24 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/29 15:58:01 by sfarhan          ###   ########.fr       */
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

void	draw_mini_square(int x, int y, t_window *window, t_minimap *mini, int color)
{
	int	square_x;
	int	square_y;
	int	temp_x;

	square_x = (x + window->player_size);
	square_y = (y + window->player_size);
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

void	innit_minimap(t_window *window, t_minimap *mini)
{
	mini->img = mlx_new_image(window->mlx, WINDOW_WIDTH / 5, WINDOW_HEIGHT / 4);
	mini->addr = mlx_get_data_addr(mini->img, &mini->bits_per_pixel,
			&mini->line_length, &mini->endian);
}

void	zoom_in(t_window *window, t_minimap *mini, char **map)
{
	int	y_start;
	int	y_end;
	int	x_start;
	int	x_end;
	int	y = 0;
	int x;

	x_start = (window->y / 40) - (WINDOW_WIDTH / 5 / 2 / 40);
	x_end = ((window->y / 40) + (WINDOW_WIDTH / 5 / 2 / 40));
	y_start = ((window->x / 40) - (WINDOW_HEIGHT / 4 / 2 / 40));
	y_end = ((window->x / 40) + (WINDOW_HEIGHT / 4 / 2 / 40));
	window->player_size = TILE_SIZE;
	while (map[y_start] && y_start <= y_end)
	{
		x = 0;
		x_start = (window->y / 40) - (WINDOW_WIDTH / 5 / 2 / 40);
		while (x_start <= x_end)
		{
			if (map[y_start][x_start] && map[y_start][x_start] == '1')
				draw_mini_square(x * 40, y * 40, window, mini, SKIN);
			else if (map[y_start][x_start]
				&& ft_strchr(map[y_start][x_start], "0NSWE"))
				draw_mini_square(x * 40, y * 40, window, mini, BEIGE);
			x_start++;
			x++;
		}
		y_start++;
		y++;
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
	window->player_size = TILE_SIZE;
	draw_background(&mini);
	zoom_in(window, &mini, map);
	window->player_size = 10;
	draw_mini_square(WINDOW_WIDTH / 5 / 2, WINDOW_HEIGHT / 4 / 2,
		window, &mini, RED);
	mlx_put_image_to_window(window->mlx, window->win, mini.img, 0, 0);
}
