SRCS = main.c

OBJ = $(SRCS:.c=.o)
NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX_PATH = mlx/

MLX_LIB = $(MLX_PATH)libmlx.a

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit


all: subsystems $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I/opt/X11/include -Imlx -c -o $@ $<

subsystems:
	@echo $(B)
	make -C $(MLX_PATH) all

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re