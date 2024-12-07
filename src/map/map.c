/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:25:17 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 11:33:26 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static t_clip	*get_tiled_clip2(t_tiled_data *t, unsigned char num)
{
	int	i;

	i = 0;
	while (!(num >> 7 != 1 && num & 1))
	{
		num = num << 1 | num >> 7;
		i++;
	}
	i /= 2;
	if (num == 1)
		return (&t->outer_corners[(i + 3) % 4]);
	if (num == 7 || num == 3)
		return (&t->edges[(i + 1) % 4]);
	if (num == 31 || num == 15 || num == 27)
		return (&t->inner_corners[i % 4]);
	if (num == 99)
		return (&t->inner_corners[(i + 1) % 4]);
	return (&t->main_tile);
}

static t_clip	*get_tiled_clip(t_map_data *map, t_tiled_data *t, int r, int c)
{
	unsigned char	num;
	t_point			*points;
	int				i;
	int				_c;
	int				_r;
		
	if (map->blocks[r][c] == '0')
		return (&t->main_tile);
	points = (t_point [8]){{-1, -1}, {0, -1}, {1, -1}, {1, 0}, \
						{1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
	/*
	012
	7 3
	654
	*/
	num = 0;
	i = 0;
	while (i < 8)
	{
		_r = r + points[i].y;
		_c = c + points[i].x;
		num <<= 1;
		i++;
		if (_c < 0 || _c >= map->cols || _r < 0 || _r >= map->rows)
				continue;
		if (map->blocks[_r][_c] == '0')
			num |= 1;
	}
	if (!num)
		return  (&t->alternate[1]);
	else
		return (get_tiled_clip2(t, num));
	return (0);
}

int	init_tiled_blocks(t_tiled **tileds_r, t_map_data *map, t_tiled_data *t)
{
	int	r;
	int	c;

	*tileds_r = malloc(sizeof(t_tiled) * map->rows * map->cols);
	if (!*tileds_r)
		return (-1);
	r = 0;
	while (r < map->rows)
	{
		c = 0;
		while (c < map->cols)
		{
			ft_printf("%c ", map->blocks[r][c]);
			load_tiled(&(*tileds_r)[r * map->cols + c], \
						&t->spr.image, \
						get_tiled_clip(map, t, r, c));
			(*tileds_r)[r * map->cols + c].obj.loc.x = c * t->size;
			(*tileds_r)[r * map->cols + c].obj.loc.y = r * t->size;
			c++;
		}
		r++;
		ft_printf("\n");
	}
	ft_printf("\n");
	return (0);
}

static int	render_map(t_map *map, t_image *frame)
{
	int	i;
	int	blocks_count;
	int (*render_p)(void *, t_image *);

	if (!map || !frame || !frame->buffer)
		return (-1);
	if (render_sprites((void *)map, frame) != 0)
		return (-1);
	blocks_count = map->s_map.rows * map->s_map.cols;
	i = 0;
	while (i < blocks_count)
	{
		render_p = (void *)map->tileds[i].obj.render;
		if (render_p && render_p(&map->tileds[i], frame) != 0)
			return (-1);
		i++;
	}
	render_p = map->components.spr.obj.render;
	if (render_p && render_p(&map->components, frame) != 0)
		return (-1);
	return (0);
}

int	load_map(t_map *map, void *mlx_ptr, char *map_path)
{
	int	err;
	err = map_parser(&map->o_map, map_path);
	if (err)
		return (err);

	err = scale_map(&map->s_map, &map->o_map);
	if (err)
		return (err);
	if (load_tiled_data((void *)map, mlx_ptr, TILEDS_PATH, TILED_SIZE) != 0)
		return (-1);
	if (init_tiled_blocks(&map->tileds, &map->s_map, &map->tiled_data) != 0)
		return (-1);
	if (load_components(&map->components, mlx_ptr, &map->o_map) != 0)
		return (-1);
	map->tiled_data.spr.obj.render = render_map;
	return (0);
}