NAME = cub3D

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
		draw_minimap.c \

all : $(NAME)

$(NAME) : $(SRCS)
		gcc $(FLAGS) $(SRCS) -o cub3D #-fsanitize=address -g

clean :
		rm -rf $(NAME)

fclean : clean
		rm -rf $(NAME)

re : fclean all