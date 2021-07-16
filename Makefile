NAME		:= fdf
SRCS		:= srcs/main.c \
				srcs/bresenham_line_algorithm.c \
				srcs/bresenham_aux.c \
				srcs/events.c \
				srcs/error.c \
				srcs/parser.c \
				srcs/parser_aux.c \
				srcs/draw_map.c \
				srcs/draw_map_aux.c \
				srcs/utils.c
OBJS		:= $(SRCS:.c=.o)
HEADERFILES	:= fdf.h
LIBFT		:= libft/libft.a
MINILIBX	:= minilibx/libmlx.a
CC			= gcc
RM			= rm -f
COMMON		=
CFLAGS		?= -Wall -Werror -Wextra $(COMMON)
LDFLAGS		?= -L minilibx/ -lmlx -framework OPENGL -framework Appkit -L libft/ -lft $(COMMON)
SANITIZE	= -g3 -fsanitize=address

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c $(HEADERFILES)
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(MINILIBX):
	$(MAKE) -C minilibx/

$(LIBFT):
	$(MAKE) -C libft/

debug:	COMMON += $(SANITIZE)
debug:	re

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C libft/
	$(MAKE) clean -C minilibx/

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft/

re: fclean all

.PHONY: all clean fclean re debug