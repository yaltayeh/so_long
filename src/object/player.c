/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:42:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/08 14:27:22 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

int update_player(t_player *player)
{
	player->clip.y = player->logs_count * 20 * 64;
	player->clip.y += player->movement * 4 * 64;
	if (player->movement == SLASH_128)
	{
		player->clip.x = player->spr.index * 128;
		player->clip.y += player->direction * 128;
		player->clip.width = 128;
		player->clip.height = 128;
	}
	else 
	{
		player->clip.x = player->spr.index * 64;
		player->clip.y += player->direction * 64;
		player->clip.width = 64;
		player->clip.height = 64;
	}
	if (player->movement == WALK)
	{
		if (player->is_walk)
		{
			if (player->direction == FRONT)
				player->spr.obj.location.y += player->speed;
			else if (player->direction == BACK)
				player->spr.obj.location.y -= player->speed;
			else if (player->direction == LEFT)
				player->spr.obj.location.x -= player->speed;
			else if (player->direction == RIGHT)
				player->spr.obj.location.x += player->speed;
			return (1);
		}
		return (0);
	}
	return (1);
}

int	load_player(t_player *player, t_components *components)
{
	load_sprites((void *)player, NULL, NULL);
	player->spr.image = components->images[PLAYER];
	player->spr.obj.location = (t_point){0, 0};
	player->spr.obj.center_point = (t_point){32, 32};
	player->spr.delay = PLAYER_DELEY;
	player->spr.index = 0;
	player->spr.max_index = 9;
	player->spr.nb_clip = 1;
	player->spr.clips = &player->clip;
	player->clip = (t_clip){0, 0, 64, 64};
	player->logs_count = 0;
	player->movement = WALK;
	player->direction = FRONT;
	player->speed = 20;
	player->spr.update = update_player;
	return (0);
}