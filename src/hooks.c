/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 22:58:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/01 17:15:30 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_game *game)
{
	t_player	*p;
	int			nb_collect;

	p = game->player;
	nb_collect = game->gs->map.nb_collect;
	if (keycode == KEY_UP \
		|| keycode == KEY_DOWN \
		|| keycode == KEY_RIGHT \
		|| keycode == KEY_LEFT)
		player_walk(p, keycode);
	if (keycode == KEY_SPACE)
	{
		if (p->logs_count >= nb_collect)
			if (is_surround_boat(game))
				ride_boat(game);
		player_slash(p);
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
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
		end_program(game, 0);
	return (0);
}

int	rander(t_game *game)
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

int	cross_button(t_game *game)
{
	end_program(game, 0);
	return (0);
}
