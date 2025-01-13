/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:15:36 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/12 08:09:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "so_long.h"
#include <sys/time.h>
#include <X11/X.h>

int end_program(t_game *game)
{
	// if (game->gs)
	// 	destroy_schema((void **)&game->gs);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	printf("Bye\n");
	exit(0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode == KEY_UP \
		|| keycode == KEY_DOWN \
		|| keycode == KEY_RIGHT \
		|| keycode == KEY_LEFT)
		game->player->is_walk = 0;
	if (keycode == KEY_SPACE)
	{
		game->player->movement = WALK;
		game->player->spr.max_index = 9;
		game->player->spr.index = 0;
	}
	if (keycode == KEY_ESC)
		end_program(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*p;

	p = game->player;
	if (keycode == KEY_UP \
		|| keycode == KEY_DOWN \
		|| keycode == KEY_RIGHT \
		|| keycode == KEY_LEFT)
		{
		return (player_walk(keycode, game));
		}
	if (keycode == KEY_SPACE)
	{
		if (p->movement != SLASH_128)
		{
			p->movement = SLASH_128;
			p->spr.index = 0;
			p->spr.max_index = 6;
		}
	}
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
	// if (!game.gs)
	// 	return (EXIT_FAILURE);
	if (check_schema(game.gs, argv[1]) != 0)
		return (-1);
	game.width = WIN_WIDTH;
	game.height = WIN_HEIGHT;
	game.mlx_ptr = mlx_init();
	// if (game.mlx_ptr == NULL)
    //     return (EXIT_FAILURE);

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

	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win_ptr, DestroyNotify, 0, end_program, &game);
	// start loop
	game.last_rander = 0;
	game.time = 0;
	mlx_loop_hook(game.mlx_ptr, rander, &game);
    mlx_loop(game.mlx_ptr);
    return (EXIT_SUCCESS);
}