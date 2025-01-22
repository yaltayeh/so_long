/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:27:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/20 18:47:15 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tile.h"

void	animate_floor(t_floor *f)
{
	int	offset;

	offset = f->size * 3 * f->spr.index;
	f->big_spot = (t_clip){offset + 0, 0, 64, 64, 0};
	f->small_spot = (t_clip){offset + 0, 64, 64, 64, 0};
	f->tileds[0] = (t_clip){offset + 64, 64, 64, 64, 0};
	f->tileds[1] = (t_clip){offset + 64, 0, 64, 64, 0};
	f->tileds[2] = (t_clip){offset + 64 * 2, 0, 64, 64, 0};
	f->tileds[3] = (t_clip){offset + 64 * 2, 64, 64, 64, 0};
	f->tileds[4] = (t_clip){offset, 64 * 4, 64, 64, 0};
	f->tileds[5] = (t_clip){offset, 64 * 2, 64, 64, 0};
	f->tileds[6] = (t_clip){offset + 64 * 2, 64 * 2, 64, 64, 0};
	f->tileds[7] = (t_clip){offset + 64 * 2, 64 * 4, 64, 64, 0};
	f->tileds[8] = (t_clip){offset + 64, 64 * 2, 64, 64, 0};
	f->tileds[9] = (t_clip){offset + 64 * 2, 64 * 3, 64, 64, 0};
	f->tileds[10] = (t_clip){offset + 64, 64 * 4, 64, 64, 0};
	f->tileds[11] = (t_clip){offset, 64 * 3, 64, 64, 0};
	f->tileds[12] = (t_clip){offset + 64, 64 * 3, 64, 64, 0};
	f->tileds[13] = (t_clip){offset, 64 * 5, 64, 64, 0};
	f->tileds[14] = (t_clip){offset + 64, 64 * 5, 64, 64, 0};
	f->tileds[15] = (t_clip){offset + 64 * 2, 64 * 5, 64, 64, 0};
}

int	load_floor(t_floor *f, int size)
{
	if (load_sprites(&f->spr) == -1)
		return (-1);
	ft_strlcpy((char *)f, "tiled_data", NAME_SIZE);
	f->size = size;
	f->spr.index = 0;
	f->spr.max_index = 4;
	f->spr.clips = NULL;
	f->spr.animate = animate_floor;
	f->spr.delay = TILED_DELEY;
	f->spr.obj.render = NULL;
	return (0);
}

int	load_tile(t_tile *tile, t_schema *schema, t_clip *clip, t_object *parent)
{
	load_sprites((void *)tile);
	ft_strlcpy((char *)tile, "tile", NAME_SIZE);
	tile->spr.image = schema_get_image_by_name(schema, "tile");
	if (!tile->spr.image)
		return (-1);
	if (parent)
		tile->spr.obj.parent_location = &parent->absolute_location;
	tile->spr.clips = clip;
	tile->spr.nb_clip = 1;
	return (0);
}
