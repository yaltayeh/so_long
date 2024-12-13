/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:42:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/13 12:19:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"
#include "game_schema.h"
#include "math.h"

double		distance_2points(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

t_point	valid_move(t_map_data *o_map, t_map_data *s_map, \
					t_point current_point, t_point new_point)
{
	int	new_r;
	int	new_c;
	t_point	circle_center;

	new_c = new_point.x / TILED_SIZE;
	new_r = new_point.y / TILED_SIZE;
	if (new_c < 0 || new_c > s_map->cols || new_r < 0 || new_r > s_map->rows)
		return (current_point);
	if (s_map->blocks[new_r][new_c] == '1')
		return (current_point);

	new_c = new_point.x / (TILED_SIZE * 2);
	new_r = new_point.y / (TILED_SIZE * 2);
	if (new_c < 0 || new_c > o_map->cols || new_r < 0 || new_r > o_map->rows)
		return (current_point);
	if (o_map->blocks[new_r][new_c] == 'F' || o_map->blocks[new_r][new_c] == 'C')
	{
		circle_center.x = new_c * (TILED_SIZE * 2) + TILED_SIZE;
		circle_center.y = new_r * (TILED_SIZE * 2) + TILED_SIZE;
		// printf("%f\n", distance_2points(circle_center, new_point));
		if (distance_2points(circle_center, new_point) < 18.0f)
			return (current_point);
	}
	
	return (new_point);
}

void update_player(t_player *player)
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
	player->spr.run_animate = 1;
	if (player->movement == WALK)
	{
		new_point = player->spr.obj.relative_location;
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
			player->spr.obj.relative_location = valid_move(&player->gs->map.o_map, &player->gs->map.s_map, player->spr.obj.relative_location, new_point);
		}
		else
			player->spr.run_animate = 0;
	}
}

int	load_player(t_player *player, t_game_schema *gs)
{
	load_sprites((void *)player);
	ft_strlcpy((char *)player, "player", NAME_SIZE);
	player->spr.image = schema_get_image_by_name(gs, "player");
	player->spr.obj.relative_location = (t_point){0, 0};
	player->spr.obj.center_point = (t_point){32, 32};
	player->spr.obj.update = update_player;
	player->gs = gs;
	player->spr.delay = PLAYER_DELEY;
	player->spr.index = 0;
	player->spr.max_index = 9;
	player->spr.nb_clip = 1;
	player->clip = (t_clip){0, 0, 64, 64, 1};
	player->spr.clips = &player->clip;
	player->logs_count = 0;
	player->movement = WALK;
	player->direction = FRONT;
	player->speed = PLAYER_SPEED;
	return (0);
}