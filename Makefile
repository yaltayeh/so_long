NAME = so_long

CC = cc
CFLAGS += -Wall -Wextra -Werror -O2
LDFLAGS = -L./libft -lft
INC += -I./include -I./libft/include

OBJECT_DIR = obj
SOURCE_DIR = src
BINARY_DIR = .

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_DIR = ./minilibx-linux
	MLX_FLAGS += -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
	INC += -I$(MLX_DIR)

else ifeq ($(UNAME_S), Darwin)
	MLX_DIR = ./minilibx_macos
	MLX_FLAGS += -L$(MLX_DIR) -L/usr/X11/lib	\
				-L/opt/homebrew/lib				\
				-lmlx -lXext -lX11			 	\
				-framework OpenGL -framework AppKit 
	INC += -I/usr/X11/include -I$(MLX_DIR)
endif

FILES =	main							\
		utils							\
		camera							\
		game_schema						\
		game_schema_utils				\
		hooks							\
		core/object						\
		core/object_utils				\
		core/put_image_to_image			\
		core/schema						\
		core/sprites					\
		player/player_hook				\
		player/player_movement			\
		player/player					\
		player/valid_move				\
		components/banner				\
		components/fire					\
		components/components			\
		components/boat					\
		components/tree					\
		map/map_parser					\
		map/validate/map_validation		\
		map/validate/map_validation2	\
		map/validate/map_validation_boat_path	\
		map/validate/print_map_error	\
		map/grid_utils					\
		map/tile_utils					\
		map/map							\
		map/tile_based					\

OBJECTS = $(FILES:%=$(OBJECT_DIR)/%.o)

all: submodules library $(NAME)

submodules:
	git submodule init
	git submodule update

library:
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C libft

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) $(MLX_FLAGS) -o $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

test:
	$(CC) $(CFLAGS) test/draw_test.c $(INC) $(LDFLAGS) $(MLX_FLAGS) -o test

clean:
	rm -rf $(OBJECTS)
#	@$(MAKE) -C libft clean
#	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all 

.PHONY: all clean fclean submodules re libft mlx test
