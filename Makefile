NAME = so_long

CC = cc
# CFLAGS += -Wall -Wextra -Werror
FT_FLAGS = -L./libft -lft
INCLUDE += -I./include
INCLUDE += -I./libft/include

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_DIR = ./minilibx-linux
	MLX_FLAGS += -L$(MLX_DIR) -lmlx -lXext -lX11
	INCLUDE += -I$(MLX_DIR)

else ifeq ($(UNAME_S), Darwin)
	MLX_DIR = ./minilibx_macos
	MLX_FLAGS += -L$(MLX_DIR) -L/usr/X11/lib	\
				-L /opt/homebrew/lib			\
				-lmlx -lXext -lX11		 \
				-framework OpenGL -framework AppKit 
	INCLUDE += -I/usr/X11/include -I$(MLX_DIR)
endif

SOURCES = main.c \
			load_image.c \
			2d_object/object.c \
			map/tile_parser.c \
			put_image_to_image.c \
			
# map/map_parser.c

SOURCES := $(addprefix src/, $(SOURCES))
OBJECTS = $(SOURCES:src/%.c=build/%.o)


all: submodules $(NAME)


submodules:
	git submodule init
	git submodule update

mlx:
	$(MAKE) -C $(MLX_DIR)

libft:
	@$(MAKE) -C libft

$(NAME): $(OBJECTS) | libft mlx
	$(CC) $(CFLAGS) $(OBJECTS) $(FT_FLAGS) $(MLX_FLAGS) $(INCLUDE) -o $@

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJECTS)
	$(MAKE) -C libft clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C libft fclean

re: fclean all 

.PHONY: all libft mlx clean fclean submodules re
