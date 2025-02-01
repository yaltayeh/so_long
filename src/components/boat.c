/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:26:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/01 18:59:09 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

char	get_mask_value(t_game_schema *gs, t_point new_location);

void	update_boat(t_boat *boat)
{
	t_point			new_point;
	t_player		*player;

	if (boat->move_lock)
		return ;
	player = (t_player *)get_children_by_name(&boat->gs->components, "player");
	if (!player->is_walk)
		return ;
	new_point = ((t_object *)boat)->relative_location;
	if (player->direction == FRONT)
		new_point.y += player->speed;
	else if (player->direction == BACK)
		new_point.y -= player->speed;
	else if (player->direction == LEFT)
		new_point.x -= player->speed;
	else if (player->direction == RIGHT)
		new_point.x += player->speed;
	if (player->direction == FRONT || player->direction == BACK)
		boat->direction = VERTICAL;
	else if (player->direction == RIGHT || player->direction == LEFT)
		boat->direction = HORIZONTAL;
	if (get_mask_value(boat->gs, new_point) == '1')
		((t_object *)boat)->relative_location = new_point;
}

void	animate_boat(t_boat *boat)
{
	boat->clip = (t_clip){boat->spr.index * 64, \
							boat->direction * 64, \
								64, 64, 0};
}

t_boat	*init_boat(t_game_schema *gs)
{
	t_boat	*boat;

	boat = malloc(sizeof(t_boat));
	if (!boat)
		return (NULL);
	load_sprites((void *)boat);
	ft_strlcpy((char *)boat, "boat", NAME_SIZE);
	((t_object *)boat)->center_point = (t_point){32, 32};
	((t_object *)boat)->destroy = defult_destroy_object;
	((t_object *)boat)->update = update_boat;
	((t_sprites *)boat)->image = schema_get_image_by_name(gs, "boat");
	boat->clip = (t_clip){0};
	((t_sprites *)boat)->clips = &boat->clip;
	((t_sprites *)boat)->nb_clips = 1;
	((t_sprites *)boat)->index = 0;
	((t_sprites *)boat)->max_index = 4;
	((t_sprites *)boat)->delay = 3;
	((t_sprites *)boat)->animate = animate_boat;
	boat->gs = gs;
	boat->direction = DIAGONAL;
	boat->move_lock = 1;
	boat->is_move = 0;
	return (boat);
}
