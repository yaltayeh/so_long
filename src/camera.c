/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:49:11 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/26 15:41:15 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "game_schema.h"

void	update_camera(t_camera	*camera)
{
	t_object		*player;
	t_game_schema	*gs;
	t_point			map_size;
	t_point			*location;

	gs = (t_game_schema *)camera->schema;
	player = get_children_by_name(&gs->components, "player");
	location = &camera->obj.relative_location;
	if (player)
	{
		location->x = -player->relative_location.x + WIN_WIDTH / 2;
		location->y = -player->relative_location.y + WIN_HEIGHT / 2;
		if (location->x > 0)
			location->x = 0;
		if (location->y > 0)
			location->y = 0;
		map_size.x = gs->map.s_grid.cols * TSIZE;
		map_size.y = gs->map.s_grid.rows * TSIZE;
		if (map_size.x + location->x < WIN_WIDTH)
			location->x = WIN_WIDTH - map_size.x;
		if (map_size.y + location->y < WIN_HEIGHT)
			location->y = WIN_HEIGHT - map_size.y;
	}
}

void	load_camera(t_camera *camera, void *schema)
{
	load_object(camera);
	ft_strlcpy((char *)camera, "camera", NAME_SIZE);
	camera->schema = schema;
	((t_object *)camera)->update = update_camera;
}