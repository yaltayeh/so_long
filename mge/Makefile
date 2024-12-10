NAME = libmge.a

CC = cc
LIBFT_DIR = ../libft
CFLAGS = -Wall -Wextra -Werror -I./include -I $(LIBFT_DIR)/include

SRC =	object.c				\
		put_image_to_image.c	\
		schema.c				\
		sprites.c				\

SRC := $(addprefix src/, $(SRC))
OBJ = $(SRC:src/%.c=build/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $?

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re