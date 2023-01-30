/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:21:55 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/29 15:52:12 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	last_char(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i])
	{
		if (!ft_strchr(line[i], " \t\r\v"))
			break ;
		i--;
	}
	return (i);
}

void	clear_data(char **file)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	while (file[i])
	{
		j = 0;
		len = last_char(file[i]);
		if (len != ft_strlen(file[i]) - 1)
		{
			tmp = malloc(sizeof(char) * len + 1);
			while (file[i][j] && len-- >= 0)
			{
				tmp[j] = file[i][j];
				j++;
			}
			tmp[j] = '\0';
			free (file[i]);
			file[i] = tmp;
		}
		i++;
	}
}

void	check_color(char **rgb, t_config *config, int i, int j)
{
	int	degree;

	degree = ft_atoi(&rgb[i][j]);
	if (degree < 0 || degree > 255)
	{
		free_2darray(rgb);
		handle_error(config);
	}
}

void	check_rgb(char **rgb, t_config *config)
{
	int	i;
	int	j;

	i = -1;
	if (line_counter(rgb) != 3)
		handle_error(config);
	while (rgb[++i])
	{
		clear_data(rgb);
		j = whitesp_loop(rgb[i], 0);
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
			{
				free_2darray(rgb);
				handle_error(config);
			}
			j++;
		}
		j = whitesp_loop(rgb[i], 0);
		check_color(rgb, config, i, j);
	}
}

int	line_counter(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
