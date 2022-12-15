/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saadennour <saadennour@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 06:48:19 by saadennour        #+#    #+#             */
/*   Updated: 2022/12/03 06:48:20 by saadennour       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_config    get_config(int fd)
{
    t_config    config;

    config.data = getdata(fd);
    if (mapislast(config.data, &config) == 0)
        handle_error(&config);
    get_map(&config);
    return (config);
}

void    get_map(t_config *config)
{
    mapscan(config);
    top_X_bottom(config);
    check_walls(config);
}

void    mapscan(t_config *config)
{
    int i;
    int j;
    int n;

    i = 6;
    n = 0;
    while (config->data[i])
    {
        j = 0;
        while (config->data[i][j])
        {
            if (ft_strchr(config->data[i][j], "NSWE"))
                n++;
            if (!ft_strchr(config->data[i][j], "01NSWE ") || n > 1)
                map_error(config);
            j++;
        }
        i++;
    }
}

void    top_X_bottom(t_config *config)
{
    int i;
    int max;

    i = 0;
    while (config->data[6][i])
    {
        if (config->data[6][i] != '1' && config->data[6][i] != ' ')
            map_error(config);
        i++;
    }
    max = line_counter(config->data) - 1;
    i = 0;
    while (config->data[max][i])
    {
        if (config->data[max][i] != '1' && config->data[max][i] != ' ')
            map_error(config);
        i++;
    }
}

void    check_walls(t_config *config)
{
    int i;
    int j;

    i = 7;
    while (i < line_counter(config->data) - 1)
    {
        if (!ft_strchr(config->data[i][0], "1 "))
            map_error(config);
        j = 1;
        while (config->data[i][j])
        {
            if (config->data[i][j] == ' ')
            {
                if (!ft_strchr(config->data[i][j - 1], "1 ") || !ft_strchr(config->data[i][j + 1], "1 ")
                    || !ft_strchr(config->data[i - 1][j], "1 ") || !ft_strchr(config->data[i + 1][j], "1 "))
                    map_error(config);
            }
            j++;
        }
        if (!ft_strchr(config->data[i][j - 1], "1 "))
            map_error(config);
        i++;
    }
}

// void    get_idpaths(t_config *config)
// {
//     return ;
// }

// t_colors    *get_color(int  fd)
// {
//     t_colors    *colors;

//     return (colors);
// }

void    check_extension(char *filename)
{
    int i;

    i = ft_strlen(filename) - 1;
    while (filename[i] != '.')
        i--;
    if (ft_strcmp(&filename[i], ".cub"))
    {
        printf ("Error : Filename doesn't end with .cub extension\n");
        exit (0);
    } 
}