/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:36:12 by sfarhan           #+#    #+#             */
/*   Updated: 2022/12/27 17:37:28 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	find_player(t_window *window, char **map)
{
	int	x;
	int	y;

	x = 6;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (ft_strchr(map[x][y], "NSWE"))
			{
				window->x = (x - 6) * 40 + 15;
				window->y = y * 40 + 15;
			}
			y++;
		}
		x++;
	}
}

void	minimap(char **map, t_window *window)
{
	int	i;
	int	j;
	t_data	data;

	i = 6;
	window->img = mlx_new_image(window->mlx,  40 * ft_strlen(map[6]), 40 * line_counter(&map[6]));
	data.addr = mlx_get_data_addr(window->img, &data.bits_per_pixel, &data.line_length, &data.endian);

	printf("test\n");
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(j * 40, (i - 6) * 40, &data, SKIN, 40);
			else if (ft_strchr(map[i][j], "0NSWE"))
				draw_square(j * 40, (i - 6) * 40, &data, BEIGE, 40);
			j++;
		}
		i++;
	}
	draw_player(window->y, window->x, &data, RED, 10);
	draw_circle(200, 300, &data, RED, 100);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}