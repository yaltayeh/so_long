/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:25:17 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/26 00:32:52 by yaltayeh         ###   ########.fr       */
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
	((t_sprites *)tile)->image = schema_get_image_by_name(schema, "tile");
	((t_sprites *)tile)->clips = get_tile_clip(map, &map->s_grid, r, c);
	((t_sprites *)tile)->nb_clip = 1;
	return (tile);
}

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
			// ((t_object *)tile)->relative_location.x += (c + 1) % 2;
			// ((t_object *)tile)->relative_location.y += (r + 1) % 2;
			add_children(map, tile);
			c++;
		}
		r++;
	}
	return (0);
}

void	free_grid(t_grid *grid)
{
	int		i;

	i = 0;
	if (grid->blocks)
	{
		while (i < grid->rows && grid->blocks[i])
		{
			free(grid->blocks[i]);
			i++;
		}
		free(grid->blocks);
		grid->blocks = NULL;
	}
}

void	destroy_map(t_map **map_p)
{
	t_map	*map;

	map = *map_p;
	free_grid(&map->o_grid);
	free_grid(&map->s_grid);
	free_grid(&map->p_grid);
}

// int	open_map_and_check(t_map *map, const char *map_path)
// {
// 	if (load_floor((void *)map, TSIZE) != 0)
// 		return (-1);
// 	ft_strlcpy((char *)map, "map", NAME_SIZE);
// 	map->nb_collect = map_parser(map, map_path);
// 	if (map->nb_collect < 1)
// }

void	animate_map(t_map *map)
{
	int	offset;

	offset = map->size * 3 * map->spr.index;
	map->big_spot = (t_clip){offset + 0, 0, 64, 64, 0};
	map->small_spot = (t_clip){offset + 0, 64, 64, 64, 0};
	map->tileds[0] = (t_clip){offset + 64, 64, 64, 64, 0};
	map->tileds[1] = (t_clip){offset + 64, 0, 64, 64, 0};
	map->tileds[2] = (t_clip){offset + 64 * 2, 0, 64, 64, 0};
	map->tileds[3] = (t_clip){offset + 64 * 2, 64, 64, 64, 0};
	map->tileds[4] = (t_clip){offset, 64 * 4, 64, 64, 0};
	map->tileds[5] = (t_clip){offset, 64 * 2, 64, 64, 0};
	map->tileds[6] = (t_clip){offset + 64 * 2, 64 * 2, 64, 64, 0};
	map->tileds[7] = (t_clip){offset + 64 * 2, 64 * 4, 64, 64, 0};
	map->tileds[8] = (t_clip){offset + 64, 64 * 2, 64, 64, 0};
	map->tileds[9] = (t_clip){offset + 64 * 2, 64 * 3, 64, 64, 0};
	map->tileds[10] = (t_clip){offset + 64, 64 * 4, 64, 64, 0};
	map->tileds[11] = (t_clip){offset, 64 * 3, 64, 64, 0};
	map->tileds[12] = (t_clip){offset + 64, 64 * 3, 64, 64, 0};
	map->tileds[13] = (t_clip){offset, 64 * 5, 64, 64, 0};
	map->tileds[14] = (t_clip){offset + 64, 64 * 5, 64, 64, 0};
	map->tileds[15] = (t_clip){offset + 64 * 2, 64 * 5, 64, 64, 0};
}

int	load_map(t_map *map, const char *map_path)
{
	load_sprites(map);
	ft_strlcpy((char *)map, "map", NAME_SIZE);

	((t_sprites *)map)->index = 0;
	((t_sprites *)map)->max_index = 4;
	((t_sprites *)map)->clips = NULL;
	((t_sprites *)map)->delay = TILED_DELEY;
	((t_sprites *)map)->obj.render = NULL;

	((t_object *)map)->destroy = destroy_map;
	((t_sprites *)map)->animate = animate_map;
	map->nb_collect = map_parser(map, map_path);
	if (map->nb_collect < 1)
		return (-1);
	map->size = TSIZE;
	return (0);
}
