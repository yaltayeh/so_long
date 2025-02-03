NAME = test.out

FILES = main					\
		component_list			\
		player					\
		component				\

OBJECTS = $(FILES:%=obj/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	cc -o $@ $(OBJECTS)

obj/%.o: %.c *.h
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(NAME)

re: clean all
