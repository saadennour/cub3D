#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

typedef struct t_idpaths
{
    char    *north_path;
    char    *south_path;
    char    *east_path;
    char    *west_path;
}   t_idpaths;

typedef struct t_colors
{
    int floor[3];
    int ceiling[3];
}   t_colors;

typedef struct t_config
{
    char    **map;
    char    **data;
    t_colors    *colors;
    t_idpaths   *idpaths;
}   t_config;

void        check_extension(char *filename);
t_config    get_config(int fd);
char	    *get_next_line(int fd);
char        **getdata(int fd);
int         mapislast(char **data, t_config *config);
void        check_id(char *data, t_config *config, int *code);
char	    **ft_split(char const *s, char c);
char	    *ft_strjoin(char *s1, char *s2);
int	        ft_strlen(char *str);
int     	ft_isdigit(int c);
int         ft_strchr(char s, char *scan);
int         ft_strncmp(const char *first, const char *second, size_t length);
int     	ft_atoi(char *str);
void        handle_error(t_config *config);
int	        ft_strcmp(char *s1, char *s2);
int         whitesp_loop(char *str, int i);
void        check_rgb(char **rgb, t_config *config);
int         line_counter(char **str);
void        map_error(t_config *config);
void        top_X_bottom(t_config *config);
void        mapscan(t_config *config);
void        get_map(t_config *config);
void        check_walls(t_config *config);
void        free_struct(t_config *config);
char    	*ft_strdup(const char *src);
void        free_2darray(char **str);



#endif