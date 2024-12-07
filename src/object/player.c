/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:42:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 11:20:56 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

int update_player(t_player *player)
{
	player->clip.y = player->logs_count * 20 * 64;
	player->clip.y += player->movement * 4 * 64;
	if (player->movement == SLASH_128)
	{
		player->clip.x = player->spr.col * 128;
		player->clip.y += player->direction * 128;
		player->clip.width = 128;
		player->clip.height = 128;
	}
	else 
	{
		player->clip.x = player->spr.col * 64;
		player->clip.y += player->direction * 64;
		player->clip.width = 64;
		player->clip.height = 64;
	}
	if (player->movement == WALK)
	{
		if (player->is_walk)
		{
			if (player->direction == FRONT)
				player->spr.obj.loc.y += player->speed;
			else if (player->direction == BACK)
				player->spr.obj.loc.y -= player->speed;
			else if (player->direction == LEFT)
				player->spr.obj.loc.x -= player->speed;
			else if (player->direction == RIGHT)
				player->spr.obj.loc.x += player->speed;
			return (1);
		}
		return (0);
	}
	return (1);
}

int	load_player(t_player *player, void *mlx_ptr)
{
	if (load_sprites((void *)player, mlx_ptr, PLAYER_PATH) == -1)
		return (-1);
	player->spr.obj.loc = (t_point){0, 0};
	player->spr.delay = PLAYER_DELEY;
	player->spr.col = 0;
	player->spr.max_col = 9;
	player->spr.clip = &player->clip;
	player->clip = (t_clip){0, 0, 64, 64};
	player->logs_count = 0;
	player->movement = WALK;
	player->direction = FRONT;
	player->speed = 20;
	player->spr.update = update_player;
	return (0);
}