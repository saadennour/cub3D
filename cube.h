/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:31:27 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/28 22:11:40 by sfarhan          ###   ########.fr       */
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
//# include "mlx/mlx.h"

# define FOV			60 * M_PI / 180
# define BEIGE			0XF0F8FF
# define SKIN			0XE9967A
# define RED			0XFF0000
# define YELLOW			0XFDF4A4
# define W				13
# define A				0
# define S				1
# define D				2
# define LEFT_ARROW		123
# define RIGHT_ARROW	124
# define NUMBER_OF_RAYS	1366
# define SCALE_DOWN		0.4
# define TILE_SIZE		40
# define WINDOW_WIDTH 	1366
# define WINDOW_HEIGHT 	768
# define MINIMAP_WIDTH	WINDOW_WIDTH / 5
# define MINIMAP_HEIGHT	WINDOW_HEIGHT / 4

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
	int	xfloor;
	int	xceil;
}				t_colors;

typedef struct t_config
{
	char		**data;
	t_colors	*colors;
	t_idpaths	*idpaths;
}				t_config;

typedef struct s_data {
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_minimap {
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*win;
	void	*img;
}				t_minimap;

typedef struct s_rays
{
	double	fh_y;
	double	fh_x;
	double	horiz_x;
	double	horiz_y;
	double	fv_x;
	double	fv_y;
	double	vert_x;
	double	vert_y;
	double	start;
	double	end;
	int		vert_distance;
	int		horiz_distance;
	double	xray;
	double	yray;
	double	*xrays;
	double	*yrays;
	int		*v_or_h;
	double	project_plane;
	double	wallheight;
}				t_rays;

typedef struct t_texture
{
	t_data	*data;
	void	*img;
	int		height;
	int		width;
}				t_texture;

typedef struct t_window
{
	t_rays		ray;
	t_data		*px;
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
	void		*mlx;
	void		*win;
	char		**map;
	void		*img;
	int			x;
	int			y;
	int			wall_x;
	int			wall_y;
	int			player_size;
	double		rotation_angle;
	double		line_x;
	double		line_y;
	double		si;
	double		co;
	int			xdirection;
	int			ydirection;
	int			height;
	int			width;
	int			floor;
	int			ceil;
}				t_window;

void		check_extension(char *filename, char *extension);
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
void		find_player(t_window *window, char **map);
int			find_wall(t_window *window, int i, int j);
int			tallest_line(char **map);
void		texture_init(t_config *config, t_window *window);
int			just_a_func(int button, int x, int y, t_window *window);
void		clear_data(char **file);
int			north_south(char *data, t_config *config, int i);
int			west_east(char *data, t_config *config, int i);
int			floor_color(t_config *config, char **rgb);
int			ceiling_color(t_config *config, char **rgb);


// DRAWING THE MAP AND ITS COMPONENTS
void		draw_minimap(char **map, t_window *window);
void		start_game(t_config *config);
void		draw_square(int x, int y, t_window *window, int color);
void		minimap(char **map, t_window *window);
void		draw_player(double x, double y, t_window *window, int color);
void		drawing_rays(t_window *window);
void		line(double x, double y, t_window *window, int color);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			facing_right(t_window *window, double angle);
int			facing_down(t_window *window, double angle);
void		draw_line(t_window *window, int x, int y, int endX, int endY);
void		first_vertical_step(t_window *window);
void		vertical_steps(t_window *window, double angle);
void		first_horizental_step(t_window *window, double angle);
void		horizental_steps(t_window *window, double angle);
void		draw_rays(t_window *window);
int			find_wall_horiz(t_window *window, int i, int j);
int			find_wall_vert(t_window *window, int i, int j);
void		tree_d_drawing(t_window *window);
int			get_pixel(t_texture *texture, int y, int x);
int			encode_rgb(int red, int green, int blue);
void		draw_floor(t_window *window);
void		draw_ceiling(t_window *window);

#endif