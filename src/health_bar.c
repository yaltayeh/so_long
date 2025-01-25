/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:02:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/25 07:31:30 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "health_bar.h"

void    health_bar_update(t_health_bar *hb)
{
	((t_object *)hb)->center_point.x = hb->rec.width / hb->rec.layer / 2;
	((t_object *)hb)->center_point.y = hb->rec.height / 2;
	hb->clip.width = hb->rec.width / hb->rec.layer;
	hb->clip.height = hb->rec.height;
	hb->clip.x = hb->rec.x;
	hb->clip.y = hb->rec.y;
	hb->clip.x += hb->rec.width - ((hb->rec.width / hb->rec.layer) * ((*hb->health_r * hb->rec.layer) / hb->damge)) / hb->rec.layer;
	hb->clip.y += 0;
}

void load_health_bar(void *schema, t_health_bar *hb, void *owner, \
					int *health_r, int type)
{
	load_sprites(hb);
	ft_strlcpy((char *)hb, "health_bar", NAME_SIZE);
	hb->owner = owner;
	((t_object *)hb)->parent_location = &hb->owner->absolute_location;
	hb->clip = (t_clip){0, 0, 0, 0, 2};
	hb->health_r = health_r;
	hb->damge = *health_r;

	if ((type >> 4) == 0)
		hb->rec = (t_clip){0, 16 * (type & 15), 192, 16, 6};
	else if ((type >> 4) == 1)
		hb->rec = (t_clip){0, 16 + 16 * (type & 15), 240, 16, 5};
	else if ((type >> 4) == 2)
		hb->rec = (t_clip){64, 112 + 16 * (type & 15), 192, 16, 6};

	hb->spr.image = schema_get_image_by_name(schema, "health_bar");
	hb->spr.clips = &hb->clip;
	hb->spr.nb_clip = 1;
	hb->spr.obj.update = health_bar_update;
}
