/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:15:36 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/02 18:34:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/X.h>

void	end_program(void *_game, int exit_status)
{
	t_game	*game;

	game = (t_game *)_game;
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr && game->frame.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->frame.img_ptr);
	if (game->gs)
		destroy_object((void **)&game->gs);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	if (exit_status == 0)
		ft_printf("Bye :)\n");
	else
		ft_printf("Error :(\n");
	exit(exit_status);
}

int	is_surround_boat(t_game *game)
{
	t_object	*boat;
	t_object	*player;
	t_point		b_location;
	t_point		p_location;

	boat = get_children_by_name(&game->gs->components, "boat");
	if (!boat)
		return (0);
	player = get_children_by_name(&game->gs->components, "player");
	if (!player)
		return (0);
	p_location = player->relative_location;
	b_location = boat->relative_location;
	if (pow(p_location.x - b_location.x, 2) \
		+ pow(p_location.y - b_location.y, 2) < 100 * 100)
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
	boat = (t_boat *)get_children_by_name(&game->gs->components, "boat");
	if (!boat)
		return ;
	((t_object *)player)->relative_location = \
			((t_object *)boat)->relative_location;
	player->move_lock = 1;
	boat->move_lock = 0;
	((t_object *)player)->parent_location = &boat->spr.obj.absolute_location;
	((t_object *)player)->relative_location = (t_point){0, 0};
}

int	game_init(t_game *game, char *map_path)
{
	ft_bzero(game, sizeof(*game));
	game->gs = init_game_schema();
	if (game->gs == NULL)
		return (-1);
	if (open_map_and_check(&game->gs->map, map_path) != 0)
		return (-1);
	game->width = WIN_WIDTH;
	game->height = WIN_HEIGHT;
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		return (-1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
						game->width, game->height, "Lumberjack");
	if (game->win_ptr == NULL)
		return (-1);
	game->frame.img_ptr = mlx_new_image(game->mlx_ptr, \
										game->width, game->height);
	if (game->frame.img_ptr == NULL)
		return (-1);
	game->frame.width = game->width;
	game->frame.height = game->height;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_boat	*boat;

	if (argc != 2)
	{
		ft_fprintf(2, "Usege: %s map.ber\n", argv[0]);
		return (1);
	}
	if (game_init(&game, argv[1]) != 0)
		end_program(&game, 1);
	load_image_data(&game.frame);
	if (load_schema(game.gs, game.mlx_ptr) != 0)
		end_program(&game, 1);
	game.player = (void *)get_children_by_name(&game.gs->components, "player");
	boat = (t_boat *)get_children_by_name(&game.gs->components, "boat");
	boat->game = &game;
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win_ptr, DestroyNotify, 0, cross_button, &game);
	game.last_rander = 0;
	game.time = 0;
	mlx_loop_hook(game.mlx_ptr, rander, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
