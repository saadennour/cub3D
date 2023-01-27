/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:21:55 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/27 16:26:35 by sfarhan          ###   ########.fr       */
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