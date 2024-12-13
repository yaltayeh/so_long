/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:25:17 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/13 14:35:30 by yaltayeh         ###   ########.fr       */
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
		i = 4 + (i + 3) % 4;	// outer corners
	else if (num == 3 || num == 7)
		i = 8 + (i + 1) % 4;	// edges	
	else if (num == 15 || num == 27 || num == 31)
		i = 0 + (i + 0) % 4;	// inner corners
	else if (num == 99)
		i = 0 + (i + 1) % 4;	// inner corners
	else
	{
		ft_fprintf(2, "unknow tiled number (%d)\n", num);
		return (&t->tileds[12]);
	}
	return (&t->tileds[i]);
}

static t_clip	*get_tiled_clip(t_map_data *map, t_tiled_data *t, int r, int c)
{
	unsigned char	num;
	t_point			*points;
	int				i;
	int				_c;
	int				_r;
		
	if (map->blocks[r][c] == '0')
		return (&t->tileds[12]);
	points = (t_point [8]){{-1, -1}, {0, -1}, {1, -1}, {1, 0}, \
						{1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
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
		return  (&t->tileds[13]);
	else
		return (get_tiled_clip2(t, num));
	return (0);
}

int	init_tiled_blocks(t_tiled **tileds_r, t_map_data *s_map, \
						t_tiled_data *t, void *schema)
{
	int		r;
	int		c;
	t_tiled	*tiled;

	*tileds_r = malloc(sizeof(t_tiled) * s_map->rows * s_map->cols);
	
	if (!*tileds_r)
		return (-1);
	r = 0;
	while (r < s_map->rows)
	{
		c = 0;
		while (c < s_map->cols)
		{
			tiled = *tileds_r + (r * s_map->cols + c);
			load_tiled(tiled, schema, get_tiled_clip(s_map, t, r, c), (void *)t);
			tiled->spr.obj.relative_location.x = c * t->size;
			tiled->spr.obj.relative_location.y = r * t->size;
			tiled->spr.obj.relative_location.x = c * t->size + (c + 1) % 2;
			tiled->spr.obj.relative_location.y = r * t->size + (r + 1) % 2;
			c++;
		}
		r++;
	}
	return (0);
}

static int	render_map(t_map *map, t_image *frame)
{
	int	i;
	int	blocks_count;

	if (!map || !frame || !frame->buffer)
		return (-1);
	update_object(map);
	animate_sprites(map);
	blocks_count = map->s_map.rows * map->s_map.cols;
	i = 0;
	while (i < blocks_count)
	{
		if (render_sprites(&map->tileds[i], frame, 0) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	load_map(t_map *map, const char *map_path)
{
	int	err;
	
	if (load_tiled_data((void *)map, TILED_SIZE) != 0)
		return (-1);
	ft_strlcpy((char *)map, "map", NAME_SIZE);

	err = map_parser(&map->o_map, map_path);
	if (err)
		return (err);
	err = scale_map(&map->s_map, &map->o_map);
	if (err)
		return (err);
	map->nb_tileds = map->s_map.rows * map->s_map.cols;
	map->tiled_data.spr.obj.render = render_map;
	return (0);
}