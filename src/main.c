/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:15:36 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/12 11:11:36 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "so_long.h"
#include <sys/time.h>
#include "X11/keysym.h"
#include <X11/X.h>

int end_program(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	printf("Bye\n");
	exit(0);
}

int	player_walk(int	keycode, t_game *game)
{
	enum e_move_type	movement;
	
	// ft_printf("key: %d\n", keycode);
	movement = WALK;
	if (keycode == KEY_UP)
		game->player->direction = BACK;
	else if (keycode == KEY_DOWN)
		game->player->direction = FRONT;
	else if (keycode == KEY_RIGHT)
		game->player->direction = RIGHT;
	else if (keycode == KEY_LEFT)
		game->player->direction = LEFT;
	else if (keycode == KEY_SPACE)
	{
		game->player->logs_count = (game->player->logs_count + 1) % 3;
		return (0);
	}
	else
		return (0);
	if (movement != game->player->movement)
	{
		game->player->movement = movement;
		game->player->spr.index = 0;
	}

	if (movement == SLASH_128)
		game->player->spr.max_index = 6;
	else
		game->player->spr.max_index = 9;
	game->player->is_walk = 1;


	int camera_speed = 20;
	if (keycode == KEY_UP)
		game->gs->camera.frame.y += camera_speed;
	else if (keycode == KEY_DOWN)
		game->gs->camera.frame.y -= camera_speed;
	else if (keycode == KEY_RIGHT)
		game->gs->camera.frame.x -= camera_speed;
	else if (keycode == KEY_LEFT)
		game->gs->camera.frame.x += camera_speed;
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN \
		|| keycode == KEY_RIGHT || keycode == KEY_LEFT)
		game->player->is_walk = 0;
	return (0);
}



int rander(t_game	*game)
{	
	t_image	*frame;

	game->time++;
	if (game->time - game->last_rander < DELAY)
		return (0);
	game->last_rander = game->time;
	frame = &game->frame;
	ft_bzero(frame->buffer, frame->height * frame->size_line);
	render_schema(game->gs, frame);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, frame->img_ptr, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
    t_game	game;

	if (argc != 2)
	{
		ft_fprintf(2, "Usege: %s map.ber\n", argv[0]);
		return (1);
	}
	game.gs = init_game_schema();

	if (check_schema(game.gs, argv[1]) != 0)
		return (-1);

	game.mlx_ptr = mlx_init();
	// if (game.mlx_ptr == NULL)
    //     return (EXIT_FAILURE);
    // game.width = game.gs->map.tiled_data.size * game.gs->map.s_map.cols;
    // game.height = game.gs->map.tiled_data.size  * game.gs->map.s_map.rows;
	game.width = WIN_WIDTH;
	game.height = WIN_HEIGHT;

	game.win_ptr = mlx_new_window(game.mlx_ptr, game.width, game.height, "Lumberjack");
    // if (game.win_ptr == NULL)
    //     return (EXIT_FAILURE);
	game.frame.img_ptr = mlx_new_image(game.mlx_ptr, game.width, game.height);
	game.frame.width = game.width;
	game.frame.height = game.height;
	load_image_data(&game.frame);

	if (load_schema(game.gs, game.mlx_ptr) != 0)
		return (-1);

	game.player = (void *)schema_get_component_by_name(game.gs, "player");

	ft_printf("player: %s\n", (char *)game.player);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, player_walk, &game);
	mlx_hook(game.win_ptr, DestroyNotify, 0, end_program, &game);
	// start loop
	game.last_rander = 0;
	game.time = 0;
	mlx_loop_hook(game.mlx_ptr, rander, &game);
    mlx_loop(game.mlx_ptr);
    return (EXIT_SUCCESS);
}