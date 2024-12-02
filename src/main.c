/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:15:36 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/02 08:13:14 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "so_long.h"
#include <sys/time.h>
#include "X11/keysym.h"
#include <X11/X.h>

int end_program(t_mlx_data *data)
{

	destroy_object(&data->player);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	printf("Bye\n");
	exit(0);
}

void	rander_character_image(t_image *bg, t_2d_object *obj)
{
	int	x;
	int	y;

	x = obj->c * obj->object.width;
	y = obj->r * obj->object.height;
	put_image_to_image(bg, &obj->sprites, 0, 0, (t_clip){x, y,64,64});
	obj->c = (obj->c + 1) % obj->col;
}

int	player_walk(int	keycode, t_mlx_data *data)
{
	int	new_r;
	
	int walk_row = 8;

	new_r = data->player->r;
	if (keycode == 126) // UP
	{
		new_r = walk_row;
		data->player->col = 8;
	}
	else if (keycode == 125) // DOWN
	{
		new_r = walk_row + 2;
		data->player->col = 8;
	}
	else if (keycode == 124) // RIGHT
	{
		new_r = walk_row + 3;
		data->player->col = 8;
	}
	else if (keycode == 123) // LEFT
	{
		new_r = walk_row + 1;
		data->player->col = 8;
	}
	if (new_r != data->player->r)
		data->last_rander = 0;
	data->player->r = new_r;
	return (0);
}


int rander(t_mlx_data	*ctx)
{
	static t_image *bg;

	if (bg == NULL)
	{
		bg = malloc(sizeof(*bg));

		bg->img_ptr = mlx_new_image(ctx->mlx_ptr, ctx->width, ctx->height);
		bg->width = ctx->width;
		bg->height = ctx->height;
		load_image(bg);

	}

	ctx->time++;
	if (ctx->time - ctx->last_rander < DELAY)
		return (0);
		
	int y = 0;
	while (y < bg->height)
	{
		int x = 0;
		while (x < bg->width)
		{
			bg->buffer[y * bg->width + x] = 0xaaaaaa;
			x++;
		}
		y++;
	}
	ctx->last_rander = ctx->time;

	char map[8][8] = {
		"11111111",
		"11111111",
		"11001111",
		"11001111",
		"11110011",
		"11110011",
		"11111111",
		"11111111"
	};


	for (int y = 0; y < 8; y++)
	{

		for (int x = 0; x < 8; x++)
		{
			if (map[y][x] == '1')
			{
				unsigned int count = 0;
				for (int i = y - 1; i <= y + 1; i++)
					for (int j = x - 1; j <= x + 1; j++)
					{
						if (i == y && j == x)
							continue;
						count <<= 1;
						if (i < 0 || i >= 8 || j < 0 || j >= 8)
							continue;
						if (map[i][j] == '0')
							count |= 1;
					}
				if (count > 0)
				{
					if (count & 1 << 6)
					{
						put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].edges[3]);
						put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].edges[0]);
					}
					else if (count & 1 << 4)
					{
						put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].edges[2]);
						put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].edges[1]);
					}
					else if (count & 1 << 3)
					{
						put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].edges[1]);
						put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].edges[2]);
					}
					else if (count & 1 << 1)
					{
						put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].edges[0]);
						put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].edges[3]);
					}
					else if (count & 1 << 7)
					{
						put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].outer_corners[3]);
						put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].inner_corners[3]);
					}
					else if (count & 1 << 5)
					{
						put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].outer_corners[2]);
						put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].inner_corners[2]);
					}
					else if (count & 1 << 2)
					{
						put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].outer_corners[1]);
						put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].inner_corners[1]);
					}
					else if (count & 1 << 0)
					{
						put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].outer_corners[0]);
						put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].inner_corners[0]);
					}
				}
				else
					put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].main_tile);
			}
			else if (map[y][x] == '0')
				put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[0].main_tile);
		}
	}
	// rander_character_image(bg, ctx->player);
	mlx_clear_window(ctx->mlx_ptr, ctx->win_ptr);
	mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, bg->img_ptr, 0, 0);
	return (0);
}

int key_release(int keycode, t_mlx_data *data)
{
	(void)keycode;
	data->player->r -= 8;
	data->player->c = 0;
	data->player->col = 7;
	return (0);
}

int key_press(int keycode, t_mlx_data *data)
{
	player_walk(keycode, data);
	return (0);
}


int main(int argc, char **argv)
{
    t_mlx_data	data;

	if (argc != 2)
	{
		ft_fprintf(2, "Usege: %s map.ber\n", argv[0]);
		// return (1);
	}

	// data.map.map = ft_init_stack(FT_POINTER, ft_strcmp, ft_strdup, free);
	// if (!data.map.map)
	// 	return (1);
	// if (map_parser(argv[1], &data) != 0)
	// {
	// 	ft_fprintf(2, "Parser Error\n");
	// 	return (1);
	// }
	// ft_printf("Map is valid\n");
	// return (0);

	
	char *sprites_path = "resources/character/knight2.xpm";
	//char *gress_tail = "resources/LPC_Base_Assets/tiles/grass2.xpm";
	char *gress_tail = "resources/LPC_Base_Assets/tiles/grass2.xpm";
	char *water_tail = "resources/LPC_Base_Assets/tiles/water2.xpm";


    data.width = 256;
    data.height = 256;
	data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (EXIT_FAILURE);
	data.player = init_character(data.mlx_ptr, sprites_path);
	data.tiles[0] = xpm_file_to_tile(gress_tail, &data);
	data.tiles[1] = xpm_file_to_tile(water_tail, &data);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Sprites");
    if (data.win_ptr == NULL)
        return (EXIT_FAILURE);


	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_hook(data.win_ptr, DestroyNotify, 0, end_program, &data);	
	// start loop
	data.last_rander = 0;
	data.time = 0;
	mlx_loop_hook(data.mlx_ptr, rander, &data);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}