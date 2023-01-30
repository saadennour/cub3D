/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:08:53 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/30 19:22:10 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	get_pixel(t_texture *texture, int y, int x)
{
	char	*dst;

	dst = texture->data->addr + (int)(y * texture->data->line_length)
		+ x % TILE_SIZE * (texture->data->bits_per_pixel / 8);
	return (*(int *)dst);
}

void	get_images(t_config *config, t_window *window)
{
	window->north->img = mlx_xpm_file_to_image(window->mlx,
			config->idpaths->north_path,
			&window->north->width, &window->north->height);
	window->south->img = mlx_xpm_file_to_image(window->mlx,
			config->idpaths->south_path,
			&window->south->width, &window->south->height);
	window->east->img = mlx_xpm_file_to_image(window->mlx,
			config->idpaths->east_path,
			&window->east->width, &window->east->height);
	window->west->img = mlx_xpm_file_to_image(window->mlx,
			config->idpaths->west_path,
			&window->west->width, &window->west->height);
	window->weapon->img = mlx_xpm_file_to_image(window->mlx,
			"textures/silah_wtsp.xpm",
			&window->weapon->width, &window->weapon->height);
}

void	image_addr(t_window *window)
{
	window->north->data->addr = mlx_get_data_addr(window->north->img,
			&window->north->data->bits_per_pixel,
			&window->north->data->line_length, &window->north->data->endian);
	window->south->data->addr = mlx_get_data_addr(window->south->img,
			&window->south->data->bits_per_pixel,
			&window->south->data->line_length, &window->south->data->endian);
	window->east->data->addr = mlx_get_data_addr(window->east->img,
			&window->east->data->bits_per_pixel,
			&window->east->data->line_length, &window->east->data->endian);
	window->west->data->addr = mlx_get_data_addr(window->west->img,
			&window->west->data->bits_per_pixel,
			&window->west->data->line_length, &window->west->data->endian);
	window->weapon->data->addr = mlx_get_data_addr(window->weapon->img,
			&window->weapon->data->bits_per_pixel,
			&window->weapon->data->line_length, &window->weapon->data->endian);
}

void	texture_init(t_config *config, t_window *window)
{
	window->north = malloc(sizeof(t_texture));
	window->east = malloc(sizeof(t_texture));
	window->west = malloc(sizeof(t_texture));
	window->south = malloc(sizeof(t_texture));
	window->weapon = malloc(sizeof(t_texture));
	window->north->data = malloc(sizeof(t_data));
	window->south->data = malloc(sizeof(t_data));
	window->east->data = malloc(sizeof(t_data));
	window->west->data = malloc(sizeof(t_data));
	window->weapon->data = malloc(sizeof(t_data));
	get_images(config, window);
	image_addr(window);
}

int	check_textures(t_config *config, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error(config);
	check_extension(file, ".xpm");
	return (0);
}
