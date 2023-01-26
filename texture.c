/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:08:53 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/25 14:42:10 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_pixel(t_texture *texture, int y, int x)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return 0;
	dst = texture->data->addr + (int)(y * texture->data->line_length) + x % TILE_SIZE * (texture->data->bits_per_pixel / 8);
	return (*(int*)dst);
}

void	texture_init(t_config *config, t_window *window)
{
	window->north = malloc(sizeof(t_texture));
	window->east = malloc(sizeof(t_texture));
	window->west = malloc(sizeof(t_texture));
	window->south = malloc(sizeof(t_texture));
	window->north->data = malloc(sizeof(t_data));
	window->south->data = malloc(sizeof(t_data));
	window->east->data = malloc(sizeof(t_data));
	window->west->data = malloc(sizeof(t_data));
	window->north->img = mlx_xpm_file_to_image(window->mlx, config->idpaths->north_path, &window->north->width, &window->north->height);
	window->south->img = mlx_xpm_file_to_image(window->mlx, config->idpaths->south_path, &window->south->width, &window->south->height);
	window->east->img = mlx_xpm_file_to_image(window->mlx, config->idpaths->east_path, &window->east->width, &window->east->height);
	window->west->img = mlx_xpm_file_to_image(window->mlx, config->idpaths->west_path, &window->west->width, &window->west->height);
	window->north->data->addr = mlx_get_data_addr(window->north->img, &window->north->data->bits_per_pixel, &window->north->data->line_length, &window->north->data->endian);
	window->south->data->addr = mlx_get_data_addr(window->south->img, &window->south->data->bits_per_pixel, &window->south->data->line_length, &window->south->data->endian);
	window->east->data->addr = mlx_get_data_addr(window->east->img, &window->east->data->bits_per_pixel, &window->east->data->line_length, &window->east->data->endian);
	window->west->data->addr = mlx_get_data_addr(window->west->img, &window->west->data->bits_per_pixel, &window->west->data->line_length, &window->west->data->endian);
}