#include "cube.h"

void    handle_error(t_config *config)
{
    printf ("Error : Parsing Error\n");
    free_struct(config);
    exit (0);
}

void    map_error(t_config *config)
{
    printf ("Error : Map not valid\n");
    free_struct(config);
    exit (0);
}

int whitesp_loop(char *str, int i)
{
    while (ft_strchr(str[i], " \t\r\v\f"))
        i++;
    return (i);
}

void    check_rgb(char **rgb, t_config *config)
{
    int i;
    int j;
    int degree;

    i = -1;
    if (line_counter(rgb) != 3)
        handle_error(config);
    while (rgb[++i])
    {
        j = 0;
        while (rgb[i][j])
        {
            if (!ft_isdigit(rgb[i][j]))
            {
                free_2darray(rgb);
                handle_error(config);
            }
            j++;
        }
        degree = ft_atoi(rgb[i]);
        if (degree < 0 || degree > 255)
        {
            free_2darray(rgb);
            handle_error(config);
        }
    }
}

int line_counter(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    free_2darray(char **str)
{
    int i;

    i = 0;
    while (str[i])
        free (str[i++]);
    free (str);
}

void    free_struct(t_config *config)
{
    free_2darray(config->data);
    free (config->colors);
    free (config->idpaths);
}