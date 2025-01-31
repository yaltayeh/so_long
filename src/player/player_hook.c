/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:16:23 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/31 07:49:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"

t_point	valid_move(t_game_schema *gs, t_player *player, \
						t_point new_location);

static int	is_new_movement(t_point old_location, t_point new_location)
{
	old_location.x /= 128;
	old_location.y /= 128;
	new_location.x /= 128;
	new_location.y /= 128;
	if (ft_memcmp(&old_location, &new_location, sizeof(t_point)) == 0)
		return (0);
	return (1);
}

void	update_player(t_player *player)
{
	t_point			new_point;
	t_point			old_point;
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
		old_point = ((t_object *)player)->relative_location;
		((t_object *)player)->relative_location = valid_move(gs, player, \
																new_point);
		if (is_new_movement(old_point, ((t_object *)player)->relative_location))
			player->nb_movement += 1;
		player->spr.run_animate = 1;
	}
	if (player->movement == SLASH_128)
		if (player->touch_component \
			&& is_object_type(player->touch_component, "tree"))
			if (((t_tree *)player->touch_component)->status != 2)
				player->spr.run_animate = 1;
}

void	aminate_player(t_player *player)
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

void	end_move_player(t_player *player)
{
	t_tree	*t;

	t = (t_tree *)player->touch_component;
	if (player->movement == SLASH_128)
		if (t && ft_strncmp((char *)t, "tree", NAME_SIZE) == 0)
			if (damage_tree(t, 50) == 1)
				player->logs_count++;
}
