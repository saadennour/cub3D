/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:43:24 by aelaoufi          #+#    #+#             */
/*   Updated: 2023/01/27 19:42:26 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

void	my_map_mlx_pixel_put(t_minimap *mini, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH / 5 || y < 0 || y >= WINDOW_HEIGHT / 4)
		return ;
	dst = mini->addr + (y * mini->line_length + x * (mini->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	innit_minimap(t_window *window, t_minimap *mini)
{
	mini->img = mlx_new_image(window->mlx, WINDOW_WIDTH / 5, WINDOW_HEIGHT / 4);
	mini->addr = mlx_get_data_addr(mini->img, &mini->bits_per_pixel, &mini->line_length, &mini->endian);
}

void	draw_mini_square(int x, int y, t_window *window, t_minimap *mini, int color)
{
	int square_x;
	int square_y;
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

void	draw_minimap(char **map, t_window *window)
{
	t_minimap mini;
	int	i;
	int	j;

	i = 0;
	window->player_size = TILE_SIZE;
	innit_minimap(window, &mini);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_mini_square(SCALE_DOWN * (j * TILE_SIZE), SCALE_DOWN * (i - 6) * TILE_SIZE, window, &mini, BEIGE);
			else if (ft_strchr(map[i][j], "0NSWE"))
				draw_mini_square(SCALE_DOWN * (j * TILE_SIZE), SCALE_DOWN * (i - 6) * TILE_SIZE, window, &mini, SKIN);
			j++;
		}
		i++;
	}
	window->player_size = SCALE_DOWN * 10;
	draw_mini_square(SCALE_DOWN * (window->y - 5), SCALE_DOWN * (window->x - 5), window, &mini, RED);
	//draw_player(window->y, window->x, window, RED);
	mlx_put_image_to_window(window->mlx, window->win, mini.img, 0, 0);
}