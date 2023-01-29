/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:59:08 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/29 21:41:00 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	only_rgb(t_config *config, char *data, int i, int start)
{
	int	count;

	count = 0;
	while (data[i])
	{
		if (data[i] == ',')
			count++;
		i++;
	}
	if (ft_strncmp(&data[start], "F ", 2) == 0
		|| ft_strncmp(&data[start], "C ", 2) == 0)
	{
		if (count != 2)
			handle_error(config);
	}
}

int	check_emptyline(char *data)
{
	int	i;

	i = 0;
	while (data[i] && ft_strchr(data[i], "10NSWE \t\r\v\n"))
		i++;
	if (ft_strlen(data) == i && ft_strcmp(data, "\n"))
		return (1);
	return (0);
}

int	check_ifallone(char *data)
{
	int	i;

	i = 0;
	while (data[i] && ft_strchr(data[i], "1 \t\r\v\n"))
		i++;
	if (ft_strlen(data) == i && ft_strcmp(data, "\n"))
		return (1);
	return (0);
}

int	check_previous(char *data)
{
	int	i;

	i = ft_strlen(data) - 2;
	while (data[i] && ft_strchr(data[i], "1 \t\r\v"))
		i--;
	if (i == 0 || data[i] == '\n')
		return (1);
	return (0);
}
