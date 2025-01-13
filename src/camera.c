/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:49:11 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 07:36:25 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "game_schema.h"

void	update_camera(t_camera	*camera)
{
	t_object		*player;
	t_game_schema	*gs;
	t_point			map_size;

	gs = (t_game_schema *)camera->schema;
	player = schema_get_component_by_name(camera->schema, "player");
	if (player)
	{
		camera->frame.x = -player->relative_location.x + WIN_WIDTH / 2;
		camera->frame.y = -player->relative_location.y + WIN_HEIGHT / 2;

		if (camera->frame.x > 0)
			camera->frame.x = 0;
		if (camera->frame.y > 0)
			camera->frame.y = 0;
		map_size.x = gs->map.s_grid.cols * TSIZE;
		map_size.y = gs->map.s_grid.rows * TSIZE;
		if (map_size.x + camera->frame.x < WIN_WIDTH)
			camera->frame.x = WIN_WIDTH - map_size.x;
		if (map_size.y + camera->frame.y < WIN_HEIGHT)
			camera->frame.y = WIN_HEIGHT - map_size.y;
	}
}