NAME = so_long

SRC	=	a_destroy.c							\
		b_get_map.c							\
		b1_c1_helper.c						\
		c_check_map.c						\
		c1_check_map_flood_fill.c			\
		d_load_image_render.c				\
		e_move.c 							\
		f_init.c							\
		g_main.c							\
		./sources/gnl1/get_next_line.c 		\
		./sources/gnl1/get_next_line_utils.c\


OBJ = $(SRC:.c=.o)

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror -g

MLX_FLAGS = -L/usr/X11/lib -lX11 -lXext -lm

MLX_DIR = ./minilibx-linux

MLX = ./minilibx-linux/libmlx.a

LIBFTPRINTF = ./sources/printf/libftprintf.a
LIBFTPRINTF_DIR = ./sources/printf

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(MLX) $(LIBFTPRINTF) -lX11 -lXext


$(MLX):
	make -C $(MLX_DIR)

$(LIBFTPRINTF):
	make -C $(LIBFTPRINTF_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFTPRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPRINTF_DIR) fclean
	
re: fclean $(NAME)

.PHONY:	all clean fclean re 