/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repetition_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:03:49 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/28 16:15:22 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	handle_error(t_config *config)
{
	printf ("Error : Parsing Error\n");
	free_struct(config);
	exit (0);
}

void	map_error(t_config *config)
{
	printf ("Error : Map not valid\n");
	free_struct(config);
	exit (0);
}

void	free_2darray(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free (str[i++]);
	free (str);
}

void	free_struct(t_config *config)
{
	free_2darray(config->data);
	free (config->colors);
	free (config->idpaths);
}

int	whitesp_loop(char *str, int i)
{
	while (ft_strchr(str[i], " \t\r\v\f"))
		i++;
	return (i);
}
