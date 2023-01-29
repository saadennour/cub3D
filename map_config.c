/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:59:08 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/29 18:21:33 by sfarhan          ###   ########.fr       */
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
