/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:15:36 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/27 20:02:43 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <sys/time.h>
#include "X11/keysym.h"

int end_program(t_mlx_data *data)
{
	destroy_object(&data->player);
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
			obj->object.buffer[y * obj->object.width + x] = \
				obj->sprites.buffer[(y_offset + y) * obj->sprites.width  + x_offset + x];
			x++;
		}
		y++;
	}
	obj->c = (obj->c + 1) % obj->col;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, obj->object.img_ptr, 0, 0);
}

int rander(t_mlx_data	*data)
{
	static void *bg_img;
	static int *bg_buf;

	data->time++;
	if (data->time - data->last_rander < 1100)
		return (0);
	data->last_rander = data->time;

	if (bg_img == NULL)
	{
		int a, b, c;
		bg_img = mlx_new_image(data->mlx_ptr, data->width, data->height);
		bg_buf = (int *)mlx_get_data_addr(bg_img, &a, &b, &c);
		int y = 0;
		while (y < data->height)
		{
			int x = 0;
			while (x < data->width)
			{
				bg_buf[y * data->width + x] = 0xAAFFFFFF;
				x++;
			}
			y++;
		}
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, bg_img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, bg_img, 128, 128);
	rander_character_image(data, data->player);
	return (0);
}


int	player_walk(int	keycode, t_mlx_data *data)
{
	int	new_r;
	
	new_r = data->player->r;
	if (keycode == 126) // UP
	{
		new_r = 8;
		data->player->col = 9;
	}
	else if (keycode == 125) // DOWN
	{
		new_r = 10;
		data->player->col = 9;
	}
	else if (keycode == 124) // RIGHT
	{
		new_r = 11;
		data->player->col = 9;
	}
	else if (keycode == 123) // LEFT
	{
		new_r = 9;
		data->player->col = 9;
	}
	else if (keycode == 49)
	{
		new_r -= 8;
		data->player->col = 7;
		data->player->c = 0;
	}
	if (new_r != data->player->r)
		data->last_rander = 0;
	data->player->r = new_r;
	return (0);
}

int handle_keypress(int keycode, t_mlx_data	*data)
{
	printf("Key pressed: %d\n", keycode);
    if (keycode == ESC_KEYCODE)
		end_program(data);
	player_walk(keycode, data);
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
	char *sprites_path = "resources/character/body.xpm";

    data.width = 256;
    data.height = 256;
	data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (EXIT_FAILURE);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Sprites");
    if (data.win_ptr == NULL)
        return (EXIT_FAILURE);

	data.player = init_character(data.mlx_ptr, sprites_path);

	mlx_key_hook(data.win_ptr, handle_keypress, &data);
	// mlx_mouse_hook(data.win_ptr, handle_mouse, &data);
	mlx_hook(data.win_ptr, 17, 0, end_program, &data);

	data.player = init_character(data.mlx_ptr, sprites_path);

	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.player->object.img_ptr, 100, 100);
	// start loop
	data.last_rander = 0;
	data.time = 0;
	mlx_loop_hook(data.mlx_ptr, rander, &data);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}