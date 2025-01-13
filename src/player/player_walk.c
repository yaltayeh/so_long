/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_walk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:35:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/31 00:18:27 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_walk(int keycode, t_game *game)
{
	if (keycode == KEY_UP)
		game->player->direction = BACK;
	else if (keycode == KEY_DOWN)
		game->player->direction = FRONT;
	else if (keycode == KEY_RIGHT)
		game->player->direction = RIGHT;
	else if (keycode == KEY_LEFT)
		game->player->direction = LEFT;
	else
		return (0);
	if (game->player->movement != WALK)
	{
		game->player->movement = WALK;
		game->player->spr.index = 0;
		game->player->spr.max_index = 9;
	}
	game->player->is_walk = 1;
	return (0);
}
