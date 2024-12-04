/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:15:36 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/04 12:24:38 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "so_long.h"
#include <sys/time.h>
#include "X11/keysym.h"
#include <X11/X.h>

int end_program(t_game *game)
{

	// destroy_object(&game->player);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	printf("Bye\n");
	exit(0);
}

// void	rander_character_image(t_image *bg, t_object *obj)
// {
// 	int	x;
// 	int	y;

// 	x = obj->c * obj->object.width;
// 	y = obj->r * obj->object.height;
// 	put_image_to_image(bg, &obj->sprites, 0, 0, (t_clip){x, y,64,64});
// 	obj->c = (obj->c + 1) % obj->col;
// }

// int	player_walk(int	keycode, t_game *data)
// {
// 	int	new_r;
	
// 	int walk_row = 8;

// 	new_r = data->player->r;
// 	if (keycode == KEY_UP) // UP
// 	{
// 		new_r = walk_row;
// 		data->player->col = 8;
// 	}
// 	else if (keycode == KEY_DOWN) // DOWN
// 	{
// 		new_r = walk_row + 2;
// 		data->player->col = 8;
// 	}
// 	else if (keycode == KEY_RIGHT) // RIGHT
// 	{
// 		new_r = walk_row + 3;
// 		data->player->col = 8;
// 	}
// 	else if (keycode == KEY_LEFT) // LEFT
// 	{
// 		new_r = walk_row + 1;
// 		data->player->col = 8;
// 	}
// 	if (new_r != data->player->r)
// 		data->last_rander = 0;
// 	data->player->r = new_r;
// 	return (0);
// }


int rander(t_game	*game)
{
	static t_image *bg;
	static int index_tile = 0;

	if (bg == NULL)
	{
		bg = malloc(sizeof(*bg));

		bg->img_ptr = mlx_new_image(game->mlx_ptr, game->width, game->height);
		bg->width = game->width;
		bg->height = game->height;
		load_image(bg);

	}

	game->time++;
	if (game->time - game->last_rander < DELAY)
		return (0);
	load_tile_data(&game->tiles[0], index_tile);
	index_tile = ((index_tile + 1) % 4);
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
	game->last_rander = game->time;

	render_tile(game, bg);
	//rander_character_image(bg, ctx->player);
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, bg->img_ptr, 0, 0);
	return (0);
}

// int key_release(int keycode, t_game *data)
// {
// 	(void)keycode;
// 	data->player->r -= 8;
// 	data->player->c = 0;
// 	data->player->col = 7;
// 	return (0);
// }

// int key_press(int keycode, t_game *data)
// {
// 	player_walk(keycode, data);
// 	return (0);
// }


int main(int argc, char **argv)
{
    t_game	data;

	if (argc != 2)
	{
		ft_fprintf(2, "Usege: %s map.ber\n", argv[0]);
		return (1);
	}
	int err;
	if ((err = map_parser(argv[1], &data)) != 0)
	{
		ft_fprintf(2, "Parser Error %d\n", err);
		return (1);
	}
	ft_printf("rows: %d\ncols: %d\n", data.map.rows, data.map.cols);
	ft_printf("Map is valid\n");
	if (scale_map(&data.scaled_map, &data.map) == -1)
		return (-1);
	
	// for (int i = 0; i < data.scaled_map.rows; i++)
	// {
	// 	for (int j = 0; j < data.scaled_map.cols; j++)
	// 		ft_printf("%d ", data.scaled_map.map[i][j]);
	// 	ft_printf("\n");
	// }

	
	// char *sprites_path = "resources/character/knight2.xpm";
	char *gress_tail = "water_and_gress_64x642.xpm";


    data.width = BLOCK_SIZE * data.scaled_map.cols;
    data.height = BLOCK_SIZE  * data.scaled_map.rows;
	data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (EXIT_FAILURE);
	// data.player = init_character(data.mlx_ptr, sprites_path);
	data.tiles[0] = xpm_file_to_tile(gress_tail, &data);
	
	// data.boat = mlx_xpm_file_to_image("resources/RPG/Boat_64x64/Boat_64x64px2.xpm", )
	// data.tiles[1] = xpm_file_to_tile(water_tail, &data);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Sprites");
    if (data.win_ptr == NULL)
        return (EXIT_FAILURE);


	// mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_press, &data);
	//mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_hook(data.win_ptr, DestroyNotify, 0, end_program, &data);	
	// start loop
	data.last_rander = 0;
	data.time = 0;
	mlx_loop_hook(data.mlx_ptr, rander, &data);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}