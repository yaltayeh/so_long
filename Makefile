NAME = so_long

CC = cc
CFLAGS += -Wall -Wextra -Werror
FT_FLAGS = -L./mge -lmge -L./libft -lft
INCLUDE += -I./include -I./libft/include -I./mge/include

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_DIR = ./minilibx-linux
	MLX_FLAGS += -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
	INCLUDE += -I$(MLX_DIR)

else ifeq ($(UNAME_S), Darwin)
	MLX_DIR = ./minilibx_macos
	MLX_FLAGS += -L$(MLX_DIR) -L/usr/X11/lib	\
				-L/opt/homebrew/lib			\
				-lmlx -lXext -lX11		 \
				-framework OpenGL -framework AppKit 
	INCLUDE += -I/usr/X11/include -I$(MLX_DIR)
endif

SOURCES =	main.c						\
			utils.c						\
			camera.c					\
			game_schema.c				\
			player_walk.c				\
			components/fire.c			\
			components/components.c		\
			components/boat.c			\
			components/tree.c			\
			components/player.c			\
			map/tiled.c					\
			map/read_file.c				\
			map/map_parser.c			\
			map/scale_map.c				\
			map/map.c					\

SOURCES := $(addprefix src/, $(SOURCES))
OBJECTS = $(SOURCES:src/%.c=build/%.o)

all: mlx mge libft submodules $(NAME)

submodules:
	git submodule init
	git submodule update

mlx:
	$(MAKE) -C $(MLX_DIR)

libft:
	@$(MAKE) -C libft

mge:
	$(MAKE) -C mge

$(NAME): $(OBJECTS) mge/libmge.a libft/libft.a
	$(CC) $(CFLAGS) $(OBJECTS) $(FT_FLAGS) $(MLX_FLAGS) -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJECTS)
	$(MAKE) -C mge clean
#	$(MAKE) -C libft clean
#	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C mge fclean
#	$(MAKE) -C libft fclean

re: fclean all 

.PHONY: all clean fclean submodules re mge libft mlx
