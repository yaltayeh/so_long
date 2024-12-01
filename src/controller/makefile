
all: ps5_controller

ps5_controller: test_hid.c
	gcc test_hid.c -o ps5_controller \
		-I /opt/homebrew/include/hidapi \
		-L /opt/homebrew/lib \
		-lhidapi -lmlx \
		-framework OpenGL \
		-framework AppKit