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

all : $(NAME)

$(NAME) : $(SRCS)
		gcc	$(FLAGS) $(SRCS) -o cub3D

clean :
		rm -rf $(NAME)

fclean : clean
		rm -rf $(NAME)

re : fclean all