/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiled.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:27:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/10 10:08:19 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiled.h"

int	update_tiled_data(t_tiled_data *t)
{
	int offset;

	offset = t->size * 3 * t->spr.index;
	t->big_spot = (t_clip){offset + 0, 0, t->size, t->size};
	t->small_spot = (t_clip){offset + 0, t->size, t->size, t->size};
	t->inner_corners[0] = (t_clip){offset + t->size, t->size, t->size, t->size};
	t->inner_corners[1] = (t_clip){offset + t->size, 0, t->size, t->size};
	t->inner_corners[2] = (t_clip){offset + t->size * 2, 0, t->size, t->size};
	t->inner_corners[3] = (t_clip){offset + t->size * 2, t->size, t->size, t->size};
	t->outer_corners[0] = (t_clip){offset + 0, t->size * 4, t->size, t->size};
	t->outer_corners[1] = (t_clip){offset + 0, t->size * 2, t->size, t->size};
	t->outer_corners[2] = (t_clip){offset + t->size * 2, t->size * 2, t->size, t->size};
	t->outer_corners[3] = (t_clip){offset + t->size * 2, t->size * 4, t->size, t->size};
	t->edges[0] = (t_clip){offset + t->size, t->size * 2, t->size, t->size};
	t->edges[1] = (t_clip){offset + t->size * 2, t->size * 3, t->size, t->size};
	t->edges[2] = (t_clip){offset + t->size, t->size * 4, t->size, t->size};
	t->edges[3] = (t_clip){offset + 0, t->size * 3, t->size, t->size};
	t->alternate[0] = (t_clip){offset + 0, t->size * 5, t->size, t->size};
	t->alternate[1] = (t_clip){offset + t->size, t->size * 5, t->size, t->size};
	t->alternate[2] = (t_clip){offset + t->size * 2, t->size * 5, t->size, t->size};
	t->main_tile = (t_clip){offset + t->size, t->size * 3, t->size, t->size};
	return (1);
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
	t->spr.update = update_tiled_data;
	t->spr.delay = TILED_DELEY;
	t->spr.obj.render = NULL;
	return (0);
}

int	load_tiled(t_tiled *tiled, t_schema *schema, t_clip *clip)
{
	load_sprites(tiled);
	ft_strlcpy((char *)tiled, "tiled", NAME_SIZE);

	tiled->image = schema_get_image_by_name(schema, "tiled");
	if (!tiled->image)
		return (-1);
	tiled->clips = clip;
	tiled->nb_clip = 1;
	return (0);
}
