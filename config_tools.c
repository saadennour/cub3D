#include "cube.h"

char    **getdata(int fd)
{
    char    *line;
    char    *data;
    char    *copy;
    char    **file;

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
    return (file);
}

int set_idpaths(char *data, t_config *config, int i)
{
    int j;

    j = i + 2;
    j = whitesp_loop(data, j);
    if (ft_strncmp(&data[i], "NO ", 3) == 0)
    {
        config->idpaths->north_path = &data[j];
        return (2);
    }
    else if (ft_strncmp(&data[i], "SO ", 3) == 0)
    {
        config->idpaths->south_path = &data[j];
        return (4);
    }
    else if (ft_strncmp(&data[i], "WE ", 3) == 0)
    {
        config->idpaths->west_path = &data[j];
        return (8);
    }
    else if (ft_strncmp(&data[i], "EA ", 3) == 0)
    {
        config->idpaths->east_path = &data[j];
        return (16);
    }
    return (0);
}

int set_colors(char *data, t_config *config, int i)
{
    int     j;
    int     count;
    char    **rgb;

    count = -1;
    rgb = NULL;
    j = i + 1;
    j = whitesp_loop(data, j);
    rgb = ft_split(&data[j], ',');
    if (ft_strncmp(&data[i], "F ", 2) == 0)
    {
        check_rgb(rgb, config);
        while (++count < 3)
            config->colors->floor[count] = ft_atoi(rgb[count]);
        free_2darray (rgb);
        return (32);
    }
    else if (ft_strncmp(&data[i], "C ", 2) == 0)
    {
        check_rgb(rgb, config);
        while (++count < 3)
            config->colors->ceiling[count] = ft_atoi(rgb[count]);
        free_2darray (rgb);
        return (64);
    }
    free_2darray(rgb);
    return (0);
}

int mapislast(char **data, t_config *config)
{
    int i;
    int code;

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

void check_id(char *data, t_config *config, int *code)
{
    int i;

    i = 0;
    i = whitesp_loop(data, i);
    *code += set_idpaths(data, config, i);
    *code += set_colors(data, config, i);
}
