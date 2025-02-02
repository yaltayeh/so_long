NAME = so_long

CC = cc
CFLAGS += -Wall -Wextra -Werror -O2 -g
LDFLAGS = -L./libft -lft -lm
INC += -I./include -I./libft/include -I$(MLX_DIR)

OBJECT_DIR = obj
SOURCE_DIR = src
BINARY_DIR = .

MLX_DIR = ./minilibx-linux
MLX_FLAGS += -L$(MLX_DIR) -lmlx -lXext -lX11

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
		player/update_player			\
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
		map/map_normalization			\
		map/tile_based					\

OBJECTS = $(FILES:%=$(OBJECT_DIR)/%.o)

all: library $(NAME)

library:
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C libft

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) $(MLX_FLAGS) -o $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJECTS)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all 

.PHONY: all clean fclean re libft library
