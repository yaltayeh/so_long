/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiled.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:27:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/13 12:00:20 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiled.h"

void	animate_tiled_data(t_tiled_data *t)
{
	int offset;

	offset = t->size * 3 * t->spr.index;
	t->big_spot = (t_clip){offset + 0, 0, t->size, t->size, 0};
	t->small_spot = (t_clip){offset + 0, t->size, t->size, t->size, 0};
	t->tileds[0] = (t_clip){offset + t->size, t->size, t->size, t->size, 0};
	t->tileds[1] = (t_clip){offset + t->size, 0, t->size, t->size, 0};
	t->tileds[2] = (t_clip){offset + t->size * 2, 0, t->size, t->size, 0};
	t->tileds[3] = (t_clip){offset + t->size * 2, t->size, t->size, t->size, 0};
	t->tileds[4] = (t_clip){offset + 0, t->size * 4, t->size, t->size, 0};
	t->tileds[5] = (t_clip){offset + 0, t->size * 2, t->size, t->size, 0};
	t->tileds[6] = (t_clip){offset + t->size * 2, t->size * 2, t->size, t->size, 0};
	t->tileds[7] = (t_clip){offset + t->size * 2, t->size * 4, t->size, t->size, 0};
	t->tileds[8] = (t_clip){offset + t->size, t->size * 2, t->size, t->size, 0};
	t->tileds[9] = (t_clip){offset + t->size * 2, t->size * 3, t->size, t->size, 0};
	t->tileds[10] = (t_clip){offset + t->size, t->size * 4, t->size, t->size, 0};
	t->tileds[11] = (t_clip){offset + 0, t->size * 3, t->size, t->size, 0};
	t->tileds[12] = (t_clip){offset + t->size, t->size * 3, t->size, t->size, 0};
	t->tileds[13] = (t_clip){offset + 0, t->size * 5, t->size, t->size, 0};
	t->tileds[14] = (t_clip){offset + t->size, t->size * 5, t->size, t->size, 0};
	t->tileds[15] = (t_clip){offset + t->size * 2, t->size * 5, t->size, t->size, 0};
}

int	load_tiled_data(t_tiled_data *t, int size)
{
	if (load_sprites(&t->spr) == -1)
		return (-1);
	ft_strlcpy((char *)t, "tiled_data", NAME_SIZE);
	t->size = size;
	t->spr.index = 0;
	t->spr.max_index = 4;
	t->spr.clips = NULL;
	t->spr.animate = animate_tiled_data;
	t->spr.delay = TILED_DELEY;
	t->spr.obj.render = NULL;
	return (0);
}

int	load_tiled(t_tiled *tiled, t_schema *schema, t_clip *clip, t_object *parent)
{
	load_sprites((void *)tiled);
	ft_strlcpy((char *)tiled, "tiled", NAME_SIZE);

	tiled->spr.image = schema_get_image_by_name(schema, "tiled");
	if (!tiled->spr.image)
		return (-1);
	if (parent)
		tiled->spr.obj.parent_location = &parent->absolute_location;
	tiled->spr.clips = clip;
	tiled->spr.nb_clip = 1;
	return (0);
}
