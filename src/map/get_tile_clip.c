/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tile_clip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:07:18 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/12 08:07:54 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
if (num == 1)
	i = 4 + (i + 3) % 4; // outer corners
else if (num == 3 || num == 7)
	i = 8 + (i + 1) % 4; // edges	
else if (num == 15 || num == 27 || num == 31)
	i = 0 + (i + 0) % 4; // inner corners
else if (num == 99)
	i = 0 + (i + 1) % 4; // inner corners
*/
static t_clip	*select_clip(t_floor *t, unsigned char num)
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
		i = 4 + (i + 3) % 4;
	else if (num == 3 || num == 7)
		i = 8 + (i + 1) % 4;
	else if (num == 15 || num == 27 || num == 31)
		i = 0 + (i + 0) % 4;
	else if (num == 99)
		i = 0 + (i + 1) % 4;
	else
	{
		ft_fprintf(2, "unknow tiled number (%d)\n", num);
		return (&t->tileds[12]);
	}
	return (&t->tileds[i]);
}

t_clip	*get_tile_clip(t_grid *map, t_floor *t, int r, int c)
{
	unsigned char	num;
	t_point			*points;
	int				i;

	if (map->blocks[r][c] == '0')
		return (&t->tileds[12]);
	points = (t_point [8]){{-1, -1}, {0, -1}, {1, -1}, {1, 0}, \
						{1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
	num = 0;
	i = -1;
	while (++i < 8)
	{
		points[i].y += r;
		points[i].x += c;
		num <<= 1;
		if (points[i].x < 0 || points[i].x >= map->cols \
			|| points[i].y < 0 || points[i].y >= map->rows)
			continue ;
		if (map->blocks[points[i].y][points[i].x] == '0')
			num |= 1;
	}
	if (!num)
		return (&t->tileds[14]);
	return (select_clip(t, num));
}
