/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:42:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/10 19:29:41 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"
#include "game_schema.h"

t_point	valid_move(t_map_data *o_map, t_point current_point, t_point new_point)
{
	int	new_r;
	int	new_c;

	(void)current_point;
	new_c = new_point.x / (TILED_SIZE * 2);
	new_r = new_point.y / (TILED_SIZE * 2);
	if (new_c < 0 || new_c > o_map->cols || new_r < 0 || new_r > o_map->rows)
		return (current_point);
	if (o_map->blocks[new_r][new_c] == '1')
		return (current_point);
	return (new_point);
}

int update_player(t_player *player)
{
	t_point	new_point;
	
	player->clip.y = player->logs_count * 20 * 64;
	player->clip.y += player->movement * 4 * 64;
	if (player->movement == SLASH_128)
	{
		player->clip.x = player->spr.index * 128;
		player->clip.y += player->direction * 128;
		player->clip.width = 128;
		player->clip.height = 128;
		player->spr.obj.center_point = (t_point){64, 64};
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
		new_point = player->spr.obj.location;
		if (player->is_walk)
		{
			if (player->direction == FRONT)
				new_point.y += player->speed;
			else if (player->direction == BACK)
				new_point.y -= player->speed;
			else if (player->direction == LEFT)
				new_point.x -= player->speed;
			else if (player->direction == RIGHT)
				new_point.x += player->speed;
			player->spr.obj.location = valid_move(&player->gs->map.o_map, player->spr.obj.location, new_point);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	load_player(t_player *player, void *schema)
{
	load_sprites((void *)player);
	ft_strlcpy((char *)player, "player", NAME_SIZE);
	player->spr.image = schema_get_image_by_name(schema, "player");
	player->spr.obj.location = (t_point){0, 0};
	player->spr.obj.center_point = (t_point){32, 32};
	player->gs = (t_game_schema *)schema;
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