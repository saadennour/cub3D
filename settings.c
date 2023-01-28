/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:38:41 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/28 22:12:45 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	north_south(char *data, t_config *config, int i)
{
	int	j;

	j = i + 2;
	j = whitesp_loop(data, j);
	if (ft_strncmp(&data[i], "NO ", 3) == 0
		&& check_textures(config, &data[j]) == 0)
	{
		config->idpaths->north_path = &data[j];
		return (2);
	}
	else if (ft_strncmp(&data[i], "SO ", 3) == 0
		&& check_textures(config, &data[j]) == 0)
	{
		config->idpaths->south_path = &data[j];
		return (4);
	}
	return (0);
}

int	west_east(char *data, t_config *config, int i)
{
	int	j;

	j = i + 2;
	j = whitesp_loop(data, j);
	if (ft_strncmp(&data[i], "WE ", 3) == 0
		&& check_textures(config, &data[j]) == 0)
	{
		config->idpaths->west_path = &data[j];
		return (8);
	}
	else if (ft_strncmp(&data[i], "EA ", 3) == 0
		&& check_textures(config, &data[j]) == 0)
	{
		config->idpaths->east_path = &data[j];
		return (16);
	}
	return (0);
}

int	ceiling_color(t_config *config, char **rgb)
{
	int	count;

	count = -1;
	check_rgb(rgb, config);
	while (++count < 3)
		config->colors->ceiling[count] = ft_atoi(rgb[count]);
	config->colors->xceil = encode_rgb(config->colors->ceiling[0],
			config->colors->ceiling[1], config->colors->ceiling[2]);
	free_2darray (rgb);
	return (32);
}

int	floor_color(t_config *config, char **rgb)
{
	int	count;

	count = -1;
	check_rgb(rgb, config);
	while (++count < 3)
		config->colors->floor[count] = ft_atoi(rgb[count]);
	config->colors->xfloor = encode_rgb(config->colors->floor[0],
			config->colors->floor[1], config->colors->floor[2]);
	free_2darray (rgb);
	return (64);
}
