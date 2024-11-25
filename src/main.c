#include "so_long.h"

int end_program(t_mlx_data *data)
{
	destroy_object(&data->player_character);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	printf("Bye\n");
	exit(0);
}


void	rander_character_image(t_mlx_data *data, t_2d_object *obj)
{
	int	x;
	int	y;
	int x_offset;
	int y_offset;

	y_offset = obj->r * obj->object.height;
	x_offset = obj->c * obj->object.width;
	y = 0;
	while (y < obj->object.height)
	{
		x = 0;
		while (x < obj->object.width)
		{
			// ft_fprintf(2, "%5d ", y * obj->object.width + x);
			// ft_fprintf(2, "%5d ", (y_offset + y) * obj->sprites.width  + x_offset + x);
			obj->object.buffer[y * obj->object.width + x] = \
				obj->sprites.buffer[(y_offset + y) * obj->sprites.width  + x_offset + x];
			//obj->sprites.buffer[(y_offset + y) * obj->sprites.width  + x_offset + x] = 0xFFFFFFFF;
			x++;
		}
		y++;
		// ft_fprintf(2, "\n");
	}
	// ft_fprintf(2, "\n");
	obj->c = (obj->c + 1) % obj->col;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, obj->object.img_ptr, 0, 0);
}


int rander(t_mlx_data	*data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	rander_character_image(data, data->player_character);
	return (0);
}

int handle_keypress(int keycode, t_mlx_data	*data)
{
	printf("Key pressed: %d\n", keycode);
    if (keycode == ESC_KEYCODE)
		end_program(data);
	else if (keycode == 49)
		rander(data);
	else if (keycode == 126)
	{
		data->player_character->r -= 1;
		data->player_character->c = 0;
	}
	else if (keycode == 125)
	{
		data->player_character->r += 1;
		data->player_character->c = 0;
	}
	if (data->player_character->r < 0)
		data->player_character->r = 0;
	if (data->player_character->r >= data->player_character->row)
		data->player_character->r = data->player_character->row - 1;
	return (0);
}

int handle_mouse(int button, int x, int y, void *param)
{
    if (button == LEFT_CLICK)
	{
        printf("Left click at (%d, %d)\n", x, y);
	}
    else if (button == RIGHT_CLICK)
    {
        printf("Right click at (%d, %d), exiting...\n", x, y);
		end_program(param);
    }
    return (0);
}

int main(void)
{
    t_mlx_data	data;
	char *sprites_path = "resources/character/bow_and_shield.xpm";

    data.width = 256;
    data.height = 256;
	data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (EXIT_FAILURE);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Sprites");
    if (data.win_ptr == NULL)
        return (EXIT_FAILURE);

	data.player_character = init_character(data.mlx_ptr, sprites_path);

	mlx_key_hook(data.win_ptr, handle_keypress, &data);
	// mlx_mouse_hook(data.win_ptr, handle_mouse, &data);
	mlx_hook(data.win_ptr, 17, 0, end_program, &data);

	data.player_character = init_character(data.mlx_ptr, sprites_path);

	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.player_character->object.img_ptr, 100, 100);
	// start loop
	//mlx_loop_hook(data.mlx_ptr, rander, &data);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
