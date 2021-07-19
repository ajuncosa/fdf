NAME			:= fdf

SRCS_DIR		:= ./srcs
OBJS_DIR		:= ./objs
SRCS_LIST		:= main.c \
				bresenham_line_algorithm.c \
				bresenham_aux.c \
				error.c \
				parser.c \
				parser_aux.c \
				draw_map.c \
				draw_map_aux.c \
				utils.c
SRCS_LIST_BONUS := main_bonus.c \
				bresenham_line_algorithm.c \
				bresenham_aux.c \
				events.c \
				error.c \
				parser.c \
				parser_aux.c \
				draw_map.c \
				draw_map_aux.c \
				utils.c
OBJS_LIST		:= $(SRCS_LIST:.c=.o)
OBJS_LIST_BONUS := $(SRCS_LIST_BONUS:.c=.o)
SRCS			:= $(addprefix $(SRCS_DIR)/,$(SRCS_LIST))
OBJS			:= $(addprefix $(OBJS_DIR)/,$(OBJS_LIST))
SRCS_BONUS		:= $(addprefix $(SRCS_DIR)/,$(SRCS_LIST_BONUS))
OBJS_BONUS		:= $(addprefix $(OBJS_DIR)/,$(OBJS_LIST_BONUS))

HEADERFILES		:= includes/fdf.h includes/color.h includes/events.h includes/lines.h
LIBFT			:= libft/libft.a
MINILIBX		:= minilibx/libmlx.a
CC				= gcc
RM				= rm -rf
COMMON			=
CFLAGS			?= -Wall -Werror -Wextra -I includes/ -I libft/ $(COMMON)
LDFLAGS			?= -L minilibx/ -lmlx -framework OPENGL -framework Appkit -L libft/ -lft $(COMMON)
SANITIZE		= -g3 -fsanitize=address

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(LDFLAGS) $^ -o $@

bonus:	$(OBJS_BONUS) $(MINILIBX) $(LIBFT)
	$(CC) $(LDFLAGS) $^ -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERFILES)
	@mkdir -p $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(MINILIBX):
	$(MAKE) -C minilibx/

$(LIBFT):
	$(MAKE) -C libft/

debug:	COMMON += $(SANITIZE)
debug:	re

clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) clean -C libft/
	$(MAKE) clean -C minilibx/

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft/

re: fclean bonus

.PHONY: bonus all clean fclean re debug