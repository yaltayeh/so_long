/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:42:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/22 14:57:01 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "components.h"
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

	new_c = new_point.x / TSIZE;
	new_r = new_point.y / TSIZE;
	if (new_c < 0 || new_c > s_map->cols || new_r < 0 || new_r > s_map->rows)
		return (current_point);
	if (s_map->blocks[new_r][new_c] == '1' || s_map->blocks[new_r][new_c] == 'E')
		return (current_point);

	new_c = new_point.x / (TSIZE * 2);
	new_r = new_point.y / (TSIZE * 2);
	if (new_c < 0 || new_c > o_map->cols || new_r < 0 || new_r > o_map->rows)
		return (current_point);
	if (o_map->blocks[new_r][new_c] == 'F' || o_map->blocks[new_r][new_c] == 'C')
	{
		a = 0; b = 0;
		circle_center.x = new_c * (TSIZE * 2) + TSIZE;
		circle_center.y = new_r * (TSIZE * 2) + TSIZE;
		player->touch_component = schema_get_component_by_loacation(gs, circle_center);
		if (player->touch_component)
		{
			if (ft_strncmp((char *)player->touch_component, "tree", NAME_SIZE) == 0)
				{a = 30; b = 15;}
			else if (ft_strncmp((char *)player->touch_component, "fire", NAME_SIZE) == 0)
				{a = 35; b = 25;}
			if (collagen_detection(circle_center, new_point, a, b))
				return (current_point);
		}
		
	}
	player->touch_component = NULL;
	return (new_point);
}

void aminate_player(t_player *player)
{
	player->spr.run_animate = 0;
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
		if (player->spr.index & 1)
			ft_printf("\a");
		player->spr.obj.center_point = (t_point){64, 32 + 56};
	}
	else
	{
		player->clip.x = player->spr.index * 64;
		player->clip.y += player->direction * 64;
		player->clip.width = 64;
		player->clip.height = 64;
		player->spr.obj.center_point = (t_point){32, 56};
	}	
}

void update_player(t_player *player)
{
	t_point	new_point;

	if (player->movement == WALK && player->is_walk)
	{
		new_point = player->spr.obj.relative_location;
		if (player->direction == FRONT)
			new_point.y += player->speed;
		else if (player->direction == BACK)
			new_point.y -= player->speed;
		else if (player->direction == LEFT)
			new_point.x -= player->speed;
		else if (player->direction == RIGHT)
			new_point.x += player->speed;
		player->spr.obj.relative_location = valid_move(player, player->gs, &player->gs->map.o_grid, &player->gs->map.s_grid, player->spr.obj.relative_location, new_point);
		player->spr.run_animate = 1;
	}
	if (player->touch_component && ft_strncmp((char *)player->touch_component, "tree", NAME_SIZE) == 0)
		if (((t_tree *)player->touch_component)->status != 2)
			player->spr.run_animate = 1;
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

t_player	*init_player(t_game_schema *gs)
{
	t_player	*player;
	
	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	load_sprites((void *)player);
	ft_strlcpy((char *)player, "player", NAME_SIZE);
	player->spr.image = schema_get_image_by_name(gs, "player");
	player->spr.obj.relative_location = (t_point){0, 0};
	player->spr.obj.center_point = (t_point){32, 52};
	player->spr.obj.update = update_player;
	player->spr.end_move = end_move_player;
	player->spr.animate = aminate_player;
	player->gs = gs;
	player->spr.delay = PLAYER_DELEY;
	player->spr.index = 0;
	player->spr.max_index = 9;
	player->spr.nb_clip = 1;
	player->clip = (t_clip){0, 0, 64, 64, 1};
	player->spr.clips = &player->clip;
	player->logs_count = 0;
	player->is_walk = 0;
	player->movement = WALK;
	player->direction = FRONT;
	player->speed = PLAYER_SPEED;
	player->spr.obj.destroy = defult_destroy_object;
	return (player);
}