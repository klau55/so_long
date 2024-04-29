NAME    := so_long
CFLAGS    := -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX    := ./MLX42

HEADERS    := -I ./include -I $(LIBMLX)/include
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
SRCS    := so_long.c mapping.c map_validation.c player_movement.c \
		route_validation.c utils.c rendering.c mapping_utils.c
LIBFT := ./libft/libft.a
OBJS    := $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C ./libft


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS) $(LIBFT)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@$(CC) $(OBJS) $(LIBS) -o $(NAME) $(LIBFT) $(HEADERS)

clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make fclean -C ./libft

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re