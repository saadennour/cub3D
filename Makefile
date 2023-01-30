NAME = cub3D

NAME_BONUS = cub3D_bonus

FLAGS = -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit

SRCS =	main.c	\
		parsing.c	\
		config_tools.c	\
		get_next_line.c	\
		split.c			\
		str_mnp.c		\
		repetition_tools.c	\
		win_manager.c	\
		2dmap.c	\
		draw_shapes.c \
		raycasting.c \
		vertical.c \
		wall_render.c \
		texture.c \
		useful_tools.c \
		str_mnp_2.c \
		settings.c \
		extra_functions.c \
		more_extra_functions.c \
		map_config.c \

SRCS_BONUS =	cube3D_bonus/main.c	\
				cube3D_bonus/parsing.c	\
				cube3D_bonus/config_tools.c	\
				cube3D_bonus/get_next_line.c	\
				cube3D_bonus/split.c			\
				cube3D_bonus/str_mnp.c		\
				cube3D_bonus/repetition_tools.c	\
				cube3D_bonus/win_manager.c	\
				cube3D_bonus/2dmap.c	\
				cube3D_bonus/draw_shapes.c \
				cube3D_bonus/raycasting.c \
				cube3D_bonus/vertical.c \
				cube3D_bonus/wall_render.c \
				cube3D_bonus/texture.c \
				cube3D_bonus/useful_tools.c \
				cube3D_bonus/draw_minimap.c \
				cube3D_bonus/str_mnp_2.c \
				cube3D_bonus/settings.c \
				cube3D_bonus/extra_functions.c \
				cube3D_bonus/more_extra_functions.c \
				cube3D_bonus/map_config.c \
				cube3D_bonus/minimap_innit.c \

all : $(NAME)

$(NAME) : $(SRCS)
	gcc $(FLAGS) $(SRCS) -o $(NAME) #-fsanitize=address -g
	
bonus :		
	gcc $(FLAGS) $(SRCS_BONUS) -o $(NAME_BONUS) #-fsanitize=address -g

clean :
	rm -rf $(NAME) $(NAME_BONUS)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all