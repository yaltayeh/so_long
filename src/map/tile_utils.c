/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:13:24 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/27 17:29:12 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_tile	*init_tile(t_map *map, void *schema, int r, int c)
{
	t_tile	*tile;

	tile = malloc(sizeof(*tile));
	if (!tile)
		return (NULL);
	load_sprites((void *)tile);
	ft_strlcpy((char *)tile, "tile", NAME_SIZE);
	((t_object *)tile)->parent_location = \
				&((t_object *)map)->absolute_location;
	((t_object *)tile)->destroy = defult_destroy_object;
	((t_sprites *)tile)->image = schema_get_image_by_name(schema, "tile");
	((t_sprites *)tile)->clips = get_tile_clip(map, &map->s_grid, r, c);
	((t_sprites *)tile)->nb_clip = 1;
	return (tile);
}

/*
	((t_object *)tile)->relative_location.x += (c + 1) % 2;
	((t_object *)tile)->relative_location.y += (r + 1) % 2;
*/
int	init_tiles(t_map *map, void *schema)
{
	int		r;
	int		c;
	t_tile	*tile;

	r = 0;
	while (r < map->s_grid.rows)
	{
		c = 0;
		while (c < map->s_grid.cols)
		{
			tile = init_tile(map, schema, r, c);
			if (!tile)
				return (-1);
			((t_object *)tile)->relative_location.x = c * TSIZE;
			((t_object *)tile)->relative_location.y = r * TSIZE;
			add_children(map, tile);
			c++;
		}
		r++;
	}
	return (0);
}
