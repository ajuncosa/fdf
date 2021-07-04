NAME		= fdf
SRCS		= main.c bresenham_line_algorithm.c
OBJS		= $(SRCS:.c=.o)
#HEADERFILES	=
LIBFT		= libft/libft.a
MINILIBX	= minilibx/libmlx.a
CC			= gcc
RM			= rm -f
COMMON		=
CFLAGS		?= -Wall -Werror -Wextra $(COMMON)
LDFLAGS		?= -L minilibx/ -lmlx -framework OPENGL -framework Appkit -L libft/ -lft $(COMMON)
SANITIZE	= -g3 -fsanitize=address

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(LDFLAGS) $^ -o $@

all: $(NAME)

$(MINILIBX):
	make -C minilibx/

$(LIBFT):
	make -C libft/

debug:	COMMON += $(SANITIZE)
debug:	re

clean:
	$(RM) $(OBJS)
	make clean -C libft/
	make clean -C minilibx/

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re debug