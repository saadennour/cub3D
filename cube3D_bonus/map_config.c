/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:59:08 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/30 19:22:10 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

int	check_ifmap(char *data)
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

int	check_emptyline(char *line, char **data, int value)
{
	char	*copy;

	copy = *data;
	if (value == 0)
		value = check_ifmap(line);
	if (value == 1 && !ft_strcmp(line, "\n") && check_previous(*data) == 1)
		value = 2;
	else if (value == 1 && !ft_strcmp(line, "\n") && check_previous(*data) == 0)
	{
		printf ("Error\n");
		exit (0);
	}
	*data = ft_strjoin(copy, line);
	if (value == 2 && check_ifmap(line) == 1 && check_ifallone(line) == 0)
	{
		printf ("Errooooor\n");
		exit (0);
	}
	else if (value == 2 && check_ifmap(line) == 1 && check_ifallone(line) == 1)
		value = 1;
	free (copy);
	return (value);
}
