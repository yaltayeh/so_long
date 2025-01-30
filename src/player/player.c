/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:42:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 10:02:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"
#include "math.h"

static int	collagen_detection(t_point p1, t_point p2, double a, double b)
{
	return (pow(p2.x - p1.x, 2) / (a * a) + pow(p2.y - p1.y, 2) / (b * b) <= 1);
}

// static int in_map(int r, int c, t_grid *map)
// {
// 	if ((r >= 0 && r < map->rows) || (c >= 0 && c < map->cols))
// }

t_point	valid_move(t_player *player, t_game_schema *gs, \
					t_grid *o_map, t_grid *s_map, \
					t_point current_point, t_point new_point)
{
	int	new_r;
	int	new_c;
	t_point	circle_center;
	double a, b;

	new_c = new_point.x / 64;
	new_r = new_point.y / 64;
	if (new_c < 0 || new_c > s_map->cols || new_r < 0 || new_r > s_map->rows)
		return (current_point);
	if (s_map->blocks[new_r][new_c] == '1' || s_map->blocks[new_r][new_c] == 'E')
		return (current_point);

	new_c = new_point.x / (64 * 2);
	new_r = new_point.y / (64 * 2);
	if (new_c < 0 || new_c > o_map->cols || new_r < 0 || new_r > o_map->rows)
		return (current_point);
	if (o_map->blocks[new_r][new_c] == 'F' || o_map->blocks[new_r][new_c] == 'C')
	{
		a = 0; b = 0;
		circle_center.x = new_c * (64 * 2) + 64;
		circle_center.y = new_r * (64 * 2) + 64;
		player->touch_component = get_children_by_loacation(&gs->components, circle_center);
		if (player->touch_component)
		{
			if (is_object_type(player->touch_component, "tree"))
				{a = 30; b = 15;}
			else if (is_object_type(player->touch_component, "fire"))
				{a = 35; b = 25;}
			if (collagen_detection(circle_center, new_point, a, b))
				return (current_point);
		}
		
	}
	player->touch_component = NULL;
	return (new_point);
}

void update_player(t_player *player)
{
	t_point	new_point;
	t_game_schema	*gs;

	gs = (t_game_schema *)player->gs;
	player->spr.run_animate = 0;
	if (player->movement == SLASH_128)
		((t_object *)player)->center_point = (t_point){64, 32 + 56};
	else
		((t_object *)player)->center_point = (t_point){32, 56};
	if (player->movement == WALK && player->is_walk)
	{
		new_point = ((t_object *)player)->relative_location;
		if (player->direction == FRONT)
			new_point.y += player->speed;
		else if (player->direction == BACK)
			new_point.y -= player->speed;
		else if (player->direction == LEFT)
			new_point.x -= player->speed;
		else if (player->direction == RIGHT)
			new_point.x += player->speed;
		((t_object *)player)->relative_location = valid_move(player, gs, &gs->map.o_grid, &gs->map.s_grid, player->spr.obj.relative_location, new_point);
		player->spr.run_animate = 1;
	}
	if (player->movement == SLASH_128)
		if (player->touch_component && is_object_type(player->touch_component, "tree"))
			if (((t_tree *)player->touch_component)->status != 2)
				player->spr.run_animate = 1;
}

void aminate_player(t_player *player)
{
	player->clip.y = 0;
	if (player->logs_count >= 9)
		player->clip.y = 2 * 20 * 64;
	else if (player->logs_count >= 3)
		player->clip.y = 1 * 20 * 64;

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
}

void end_move_player(t_player *player)
{	
	t_tree *t;

	t = (t_tree *)player->touch_component;

	if (player->movement == SLASH_128)
		if (t && ft_strncmp((char *)t, "tree", NAME_SIZE) == 0)
			if (damage_tree(t, 50) == 1)
				player->logs_count++;
}

t_player	*init_player(void *game_schema)
{
	t_player	*player;
	
	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	load_sprites((void *)player);
	ft_strlcpy((char *)player, "player", NAME_SIZE);
	((t_object *)player)->relative_location = (t_point){0, 0};
	((t_object *)player)->center_point = (t_point){32, 52};
	((t_object *)player)->update = update_player;
	((t_object *)player)->destroy = defult_destroy_object;
	((t_sprites *)player)->image = schema_get_image_by_name(game_schema, "player");
	((t_sprites *)player)->end_move = end_move_player;
	((t_sprites *)player)->animate = aminate_player;
	((t_sprites *)player)->delay = 1;
	((t_sprites *)player)->index = 0;
	((t_sprites *)player)->max_index = 9;
	((t_sprites *)player)->nb_clips = 1;
	((t_sprites *)player)->clips = &player->clip;
	player->gs = game_schema;
	player->clip = (t_clip){0, 0, 64, 64, 1};
	player->logs_count = 0;
	player->is_walk = 0;
	player->touch_component = NULL;
	player->movement = WALK;
	player->direction = FRONT;
	player->speed = PLAYER_SPEED;
	return (player);
}