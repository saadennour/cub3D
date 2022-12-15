#include "cube.h"

int main(int ac, char **av)
{
    int         fd;
    int i=0,j=0;
    t_config    config;

    if (ac == 2)
    {
        check_extension(av[1]);
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            printf ("This map doesnt exist.\n");
            return (1);
        }
        config = get_config(fd);
        printf ("%s\n", config.idpaths->north_path);
        printf ("%s\n", config.idpaths->south_path);
        printf ("%s\n", config.idpaths->east_path);
        printf ("%s\n", config.idpaths->west_path);
        while (i < 3)
            printf ("%d\n", config.colors->floor[i++]);
        while (j < 3)
            printf ("%d\n", config.colors->ceiling[j++]);
    }
    else
        printf ("Error : There is more than one argument\n");
    return (0);
}