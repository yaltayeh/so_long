/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:15:36 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/27 17:43:21 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "so_long.h"
#include <sys/time.h>
#include <X11/X.h>

int	is_surround_boat(t_game *game);
void	ride_boat(t_game *game);


int end_program(t_game *game)
{
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr && game->frame.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->frame.img_ptr);
	if (game->gs)
		destroy_object((void **)&game->gs);
		
#ifdef __linux__
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
#endif // __linux__

	free(game->mlx_ptr);
	printf("Bye\n");
	exit(0);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*p;

	p = game->player;
	if (keycode == KEY_UP \
		|| keycode == KEY_DOWN \
		|| keycode == KEY_RIGHT \
		|| keycode == KEY_LEFT)
		player_walk(p, keycode);
	if (keycode == KEY_SPACE)
	{
		// if (game->gs->banner.nb_collect == 0)
		if (is_surround_boat(game))
			ride_boat(game);
		player_slash(p);
	}
	return (0);
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

int	is_surround_boat(t_game *game)
{
	t_grid	*o_grid;
	int	r;
	int	c;

	o_grid = &game->gs->map.o_grid;
	r = ((t_object *)game->player)->relative_location.y / (TSIZE * 2);
	c = ((t_object *)game->player)->relative_location.x / (TSIZE * 2);
	if (o_grid->blocks[r][c - 1] == 'E' \
		|| o_grid->blocks[r][c + 1] == 'E' \
		|| o_grid->blocks[r - 1][c] == 'E' \
		|| o_grid->blocks[r + 1][c] == 'E')
		return (1);
	return (0);
}

void	ride_boat(t_game *game)
{
	t_player	*player;
	t_boat		*boat;

	
	if (!is_surround_boat(game))
		return ;
	player = game->player;
	boat = (t_boat *)get_children_by_name(game->gs, "boat");
	if (!boat)
		return ;
	((t_object *)player)->relative_location = ((t_object *)boat)->relative_location;
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
	update_object(game->gs);
	animate_sprites(game->gs);
	render_object(game->gs, frame, 0);
	render_object(game->gs, frame, 1);
	render_object(game->gs, frame, 2);
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
	ft_bzero(&game, sizeof(game));
	game.gs = init_game_schema();
	if (game.gs == NULL)
		end_program(&game);
	if (open_map_and_check(&game.gs->map, argv[1]) != 0)
		end_program(&game);
	game.width = WIN_WIDTH;
	game.height = WIN_HEIGHT;
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
        end_program(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.width, game.height, "Lumberjack");
    if (game.win_ptr == NULL)
		end_program(&game);
	game.frame.img_ptr = mlx_new_image(game.mlx_ptr, game.width, game.height);
	game.frame.width = game.width;
	game.frame.height = game.height;
	load_image_data(&game.frame);

	
	if (load_schema(game.gs, game.mlx_ptr) != 0)
		end_program(&game);
	game.player = (void *)get_children_by_name(&game.gs->components, "player");

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