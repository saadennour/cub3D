/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:31:27 by sfarhan           #+#    #+#             */
/*   Updated: 2022/12/27 17:41:04 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>

# define BEIGE	0XF0F8FF
# define SKIN	0XE9967A
# define RED	0x00FF0000
# define W		13
# define A		0
# define S		1
# define D		2

typedef struct t_idpaths
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
}				t_idpaths;

typedef struct t_colors
{
	int	floor[3];
	int	ceiling[3];
}				t_colors;

typedef struct t_config
{
	char		**data;
	t_colors	*colors;
	t_idpaths	*idpaths;
}				t_config;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	rotation_speed;
	double	rotation_angle;
}				t_data;

typedef struct t_window
{
	void	*mlx;
	void	*win;
	char	**map;
	void	*img;
	t_data	*px;
	float		x;
	float		y;
	double line_x;
	double line_y;
}				t_window;


void		check_extension(char *filename);
t_config	get_config(int fd);
char		*get_next_line(int fd);
char		**getdata(int fd);
int			mapislast(char **data, t_config *config);
void		check_id(char *data, t_config *config, int *code);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *str);
int			ft_isdigit(int c);
int			ft_strchr(char s, char *scan);
int			ft_strncmp(const char *first, const char *second, size_t length);
int			ft_atoi(char *str);
void		handle_error(t_config *config);
int			ft_strcmp(char *s1, char *s2);
int			whitesp_loop(char *str, int i);
void		check_rgb(char **rgb, t_config *config);
int			line_counter(char **str);
void		map_error(t_config *config);
void		top_x_bottom(t_config *config);
void		mapscan(t_config *config);
void		get_map(t_config *config);
void		check_walls(t_config *config);
void		free_struct(t_config *config);
char		*ft_strdup(const char *src);
void		free_2darray(char **str);
int			shut(t_window *window);
int			key_hook(int keycode, t_window *window);
int			check_textures(t_config *config, char *file);
void		start_game(t_config *config);
void		minimap(char **map, t_window *window);
void    	draw_square(int x, int y, t_data *data, int color, int size);
void		find_player(t_window *window, char **map);
void		draw_circle(int x, int y, t_data *data, int color, int size);
void   		draw_player(int x, int y, t_data *data, int color, int size);

#endif