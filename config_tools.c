/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:03:38 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/29 18:56:59 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	**getdata(int fd)
{
	char	*line;
	char	*data;
	char	*copy;
	char	**file;

	data = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			copy = data;
			data = ft_strjoin(copy, line);
			free (copy);
		}
		else
			break ;
		free (line);
	}
	file = ft_split(data, '\n');
	free (data);
	clear_data(file);
	return (file);
}

int	set_idpaths(char *data, t_config *config, int i)
{
	int	code;

	code = 0;
	if (ft_strncmp(&data[i], "NO ", 3) == 0
		|| ft_strncmp(&data[i], "SO ", 3) == 0)
		code = north_south(data, config, i);
	else if (ft_strncmp(&data[i], "WE ", 3) == 0
		|| ft_strncmp(&data[i], "EA ", 3) == 0)
		code = west_east(data, config, i);
	return (code);
}

int	set_colors(char *data, t_config *config, int i)
{
	int		j;
	int		code;
	char	**rgb;

	code = 0;
	rgb = NULL;
	j = i + 1;
	j = whitesp_loop(data, j);
	only_rgb(config, data, j, i);
	// printf ("line => %s\n", data);
	rgb = ft_split(&data[j], ',');
	if (ft_strncmp(&data[i], "F ", 2) == 0)
		code = floor_color(config, rgb);
	else if (ft_strncmp(&data[i], "C ", 2) == 0)
		code = ceiling_color(config, rgb);
	else
		free_2darray(rgb);
	return (code);
}

int	mapislast(char **data, t_config *config)
{
	int	i;
	int	code;

	i = 0;
	code = 0;
	config->colors = malloc(sizeof(t_colors));
	config->idpaths = malloc(sizeof(t_idpaths));
	while (data[i])
	{
		check_id(data[i], config, &code);
		if (code != 126 && i > 4)
			handle_error(config);
		i++;
	}
	if (code == 126)
		return (1);
	return (0);
}

void	check_id(char *data, t_config *config, int *code)
{
	int	i;

	i = 0;
	i = whitesp_loop(data, i);
	*code += set_idpaths(data, config, i);
	*code += set_colors(data, config, i);
}
