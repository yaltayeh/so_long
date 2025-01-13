/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:25:17 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 12:09:30 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	init_tiles(t_tile **tiles_r, t_grid *s_map, \
						t_floor *t, void *schema)
{
	int		r;
	int		c;
	t_tile	*tile;

	*tiles_r = malloc(sizeof(t_tile) * s_map->rows * s_map->cols);
	if (!*tiles_r)
		return (-1);
	r = 0;
	while (r < s_map->rows)
	{
		c = 0;
		while (c < s_map->cols)
		{
			tile = *tiles_r + (r * s_map->cols + c);
			load_tile(tile, schema, get_tile_clip(s_map, t, r, c), (void *)t);
			tile->spr.obj.relative_location.x = c * t->size;
			tile->spr.obj.relative_location.y = r * t->size;
			// tile->spr.obj.relative_location.x += (c + 1) % 1;
			// tile->spr.obj.relative_location.y += (r + 1) % 1;
			c++;
		}
		r++;
	}
	return (0);
}

static int	render_map(t_map *map, t_image *frame)
{
	int	i;
	int	tiles_count;

	if (!map || !frame || !frame->buffer)
		return (-1);
	update_object(map);
	animate_sprites(map);
	tiles_count = map->s_grid.rows * map->s_grid.cols;
	i = 0;
	while (i < tiles_count)
	{
		if (render_sprites(&map->tiles[i], frame, 0) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	destroy_map(t_map **map_p)
{
	t_map	*map;
	int		i;

	map = *map_p;
	if (map->o_grid.blocks)
	{
		i = -1;
		while (++i < map->o_grid.rows && map->o_grid.blocks[i])
			free(map->o_grid.blocks[i]);
		free(map->o_grid.blocks);
		map->o_grid.blocks = NULL;
	}
	if (map->s_grid.blocks)
	{
		i = -1;
		while (++i < map->s_grid.rows && map->s_grid.blocks[i])
			free(map->s_grid.blocks[i]);
		free(map->s_grid.blocks);
		map->s_grid.blocks = NULL;
	}
	if (map->tiles)
		free(map->tiles);
	map->tiles = NULL;
}

int	load_map(t_map *map, const char *map_path)
{
	int	err;

	if (load_floor((void *)map, TSIZE) != 0)
		return (-1);
	ft_strlcpy((char *)map, "map", NAME_SIZE);
	err = map_parser(map, map_path);
	if (err)
		return (err);
	map->nb_tiles = map->s_grid.rows * map->s_grid.cols;
	((t_object *)map)->render = render_map;
	((t_object *)map)->destroy = destroy_map;
	return (0);
}
