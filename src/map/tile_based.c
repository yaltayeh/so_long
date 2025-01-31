/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_based.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 07:53:04 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/31 19:46:47 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tile.h"

int	blend_color(int c1, int c2);

int	render_tile(t_tile *tile, t_image *frame, int layer)
{
	render_sprites(tile, frame, layer);

	return (0);
	t_point	cur;
	t_point	draw_loc;
	int		index;

	if (layer != 0)
		return (0);
	cur.y = 0;
	while (cur.y < 64)
	{
		cur.x = 0;
		while (cur.x < 64)
		{
			draw_loc = tile->spr.obj.draw_location;
			draw_loc = add_point(draw_loc, cur);
			index = (cur.y / (64/MASK_SIZE)) * MASK_SIZE + (cur.x / (64/MASK_SIZE));
			int *c = &frame->buffer[draw_loc.y * frame->width + draw_loc.x];
			if (tile->mask[index] == '0')
				*c = 0x0000ff00;
			// else if (tile->mask[index] == '1')
			// 	*c = 0x00ff0000;
			// else if (tile->mask[index] == '*')
				// *c = 0x000000ff;
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}

t_tile	*init_tile(t_map *map, void *schema, t_cell cell)
{
	t_tile	*tile;

	tile = malloc(sizeof(*tile));
	if (!tile)
		return (NULL);
	load_sprites((void *)tile);
	ft_strlcpy((char *)tile, "tile", NAME_SIZE);
	((t_object *)tile)->parent_location = \
				&((t_object *)map)->draw_location;
	((t_object *)tile)->destroy = defult_destroy_object;
	((t_object *)tile)->render = render_tile;
	((t_sprites *)tile)->image = schema_get_image_by_name(schema, "tile");
	tile->index = get_tile_index(&map->x2_grid, cell);
	tile->mask = get_tile_mask(tile->index);
	tile->cell = cell;
	((t_sprites *)tile)->clips = &map->tileds[tile->index];
	((t_sprites *)tile)->nb_clips = 1;
	return (tile);
}

/*
	((t_object *)tile)->relative_location.x += (c + 1) % 2;
	((t_object *)tile)->relative_location.y += (r + 1) % 2;
*/
int	init_tiles(t_map *map, void *schema)
{
	t_cell	cell;
	t_tile	*tile;

	cell.r = 0;
	while (cell.r < map->x2_grid.rows)
	{
		cell.c = 0;
		while (cell.c < map->x2_grid.cols)
		{
			tile = init_tile(map, schema, cell);
			if (!tile)
				return (-1);
			((t_object *)tile)->relative_location.x = cell.c * 64;
			((t_object *)tile)->relative_location.y = cell.r * 64;
			add_children(map, tile);
			cell.c++;
		}
		cell.r++;
	}
	return (0);
}
