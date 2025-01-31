/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:35:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/31 15:47:08 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"
#include "components.h"
#include "config.h"
#include "math.h"

void		player_walk(t_player *player, int keycode)
{
	if (keycode == KEY_UP)
		player->direction = BACK;
	else if (keycode == KEY_DOWN)
		player->direction = FRONT;
	else if (keycode == KEY_RIGHT)
		player->direction = RIGHT;
	else if (keycode == KEY_LEFT)
		player->direction = LEFT;
	else
		return ;
	if (player->movement != WALK)
	{
		player->movement = WALK;
		((t_sprites *)player)->index = 0;
		((t_sprites *)player)->max_index = 9;
		player->spr.delay = 1;
	}
	player->is_walk = 1;
	return ;
}

void		player_slash(t_player *player)
{
	if (player->movement == SLASH_128)
		return ;
	if (player->touch_component \
		&& is_object_type(player->touch_component, "tree"))
	{
		if (((t_tree *)player->touch_component)->status != 2)
		{
			player->movement = SLASH_128;
			((t_sprites *)player)->index = 0;
			((t_sprites *)player)->max_index = 6;
			player->spr.run_animate = 1;
		}
	}
}

static int	collagen_detection(t_point p1, t_point p2, double a, double b)
{
	return (pow(p2.x - p1.x, 2) / (a * a) + pow(p2.y - p1.y, 2) / (b * b) <= 1);
}

int			is_detection(t_game_schema *gs, t_player *player, t_point new_location)
{
	t_point	circle_center;

	circle_center.x = (new_location.x / 128) * 128 + 64;
	circle_center.y = (new_location.y / 128) * 128 + 64;
	player->touch_component = get_children_by_loacation(&gs->components, \
															circle_center);
	if (player->touch_component)
	{
		if (is_object_type(player->touch_component, "tree"))
		{
			if (collagen_detection(circle_center, new_location, 30, 15))
				return (1);
		}
		else if (is_object_type(player->touch_component, "fire"))
		{
			if (collagen_detection(circle_center, new_location, 35, 25))
				return (1);
		}
	}
	player->touch_component = NULL;
	return (0);
}

static char	get_mask_value(t_game_schema *gs, t_point new_location)
{
	t_tile		*tile;
	t_point		tile_loc;
	t_cell		cell;
	int			index;

	tile_loc.x = (new_location.x / 64) * 64;
	tile_loc.y = (new_location.y / 64) * 64;
	tile = (t_tile *)get_children_by_loacation(&gs->map, tile_loc);
	if (!tile)
		return (0);
	cell.r = (new_location.y % 64) / (64 / MASK_SIZE);
	cell.c = (new_location.x % 64) / (64 / MASK_SIZE);
	index = cell.r * MASK_SIZE + cell.c;
	return (tile->mask[index]);
}

t_point		valid_move(t_game_schema *gs, t_player *player, \
						t_point new_location)
{
	t_point		current_location;

	current_location = ((t_object *)player)->relative_location;
	if (get_mask_value(gs, new_location) != '0')
		return (current_location);
	if (is_detection(gs, player, new_location))
			return (current_location);
	player->touch_component = NULL;
	return (new_location);
}
