/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:02:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 10:02:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "health_bar.h"

void    health_bar_update(t_health_bar *hb)
{
	int	select;
	int	clip_width;
	
	((t_object *)hb)->center_point.x = hb->rec.width / hb->rec.layer / 2;
	((t_object *)hb)->center_point.y = hb->rec.height / 2;
	hb->clip.width = hb->rec.width / hb->rec.layer;
	hb->clip.height = hb->rec.height;
	hb->clip.x = hb->rec.x;
	hb->clip.y = hb->rec.y;
	
	clip_width = hb->rec.width / hb->rec.layer;
	select = hb->rec.width - (*hb->health_r * (hb->rec.width - clip_width) / hb->damge);
	if (select)
		ft_printf("%d, %d\n", clip_width, select);
	select /= 32;
	select *= 32;
	hb->clip.x += select;
	// hb->clip.x += hb->rec.width - ((hb->rec.width / hb->rec.layer) * ((*hb->health_r * hb->rec.layer) / hb->damge)) / hb->rec.layer;
	// hb->clip.y += 0;
}

t_health_bar *init_health_bar(void *schema, void *owner, \
								int *health_r, int type)
{
	t_health_bar	*hb;

	hb = malloc(sizeof(*hb));
	if (!hb)
		return (NULL);
	load_sprites(hb);
	ft_strlcpy((char *)hb, "health_bar", NAME_SIZE);
	hb->owner = owner;
	((t_object *)hb)->parent_location = &hb->owner->absolute_location;
	((t_object *)hb)->update = health_bar_update;
	((t_sprites *)hb)->image = schema_get_image_by_name(schema, "health_bar");
	((t_sprites *)hb)->clips = &hb->clip;
	((t_sprites *)hb)->nb_clips = 1;
	
	hb->clip = (t_clip){0, 0, 0, 0, 2};
	hb->health_r = health_r;
	hb->damge = *health_r;
	if ((type >> 4) == 0)
		hb->rec = (t_clip){0, 16 * (type & 15), 192, 16, 6};
	else if ((type >> 4) == 1)
		hb->rec = (t_clip){0, 16 + 16 * (type & 15), 240, 16, 5};
	else if ((type >> 4) == 2)
	{
		if ((type & 15) % 2)
			hb->rec = (t_clip){64, 112 + 16 * (type & 15), 6 * 32, 16, 6};
		else
			hb->rec = (t_clip){64, 112 + 16 * (type & 15), 192, 16, 6};
	}
	return (hb);
}
