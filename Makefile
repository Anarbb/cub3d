NAME	:= cub3D
CC		:= gcc
CFLAGS	:= -Iinclude  -Wall -Wextra -Werror -g
HEADERS	:= include/cub3d.h
LIBFT	:= libs/libft.a
MLX		:= libs/libmlx.a
# LIBS	:= -lglfw -L/Volumes/L/.brew/opt/glfw/lib 
# LIBS	:= -ldl -lglfw -pthread -lm -lglfw
LIBS	:= -lglfw -L/Users/ybenlafk/.brew/opt/glfw/lib/
LIBS	:= -lglfw -L/Users/aarbaoui/goinfre/.brew/opt/glfw/lib/

SRCS := src/main.c \
		src/parsing/parse.c \
		src/parsing/parse_util.c \
		src/engine/raycasting.c \
		src/utils/is_map.c \
		src/engine/raycast_util.c \
		src/engine/raycast_util_1.c \
		src/utils/ft_realloc.c \
		src/utils/gnl/get_next_line_utils.c \
		src/utils/free_all.c \
		src/utils/textures.c \
		src/utils/hooks.c \
		src/utils/init_player.c \
		src/utils/ft_strcmp.c \
		src/utils/gnl/get_next_line.c \
		src/utils/get_step.c \
		src/utils/get_rgba.c \
		src/utils/mlx_draw_line.c \
		src/utils/get_dem.c \
		src/engine/skybox.c \
		src/engine/minimap.c \


OBJS := $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) ${LIBFT} -o $(NAME) $(LIBS)

%.o: %.c include/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
