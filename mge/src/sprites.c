/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:57:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/10 14:35:43 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"
#include <stdio.h>

static void	render_sprites_utils(t_sprites *spr, t_image *frame)
{
	int	i;
	t_point	location;

	i = 0;
	if (spr->obj.parent_location)
	{
		location.x = spr->obj.parent_location->x;
		location.y = spr->obj.parent_location->y;
	}
	location.x = spr->obj.location.x - spr->obj.center_point.x;
	location.y = spr->obj.location.y - spr->obj.center_point.y;
	while (spr->clips && i < spr->nb_clip)
	{
		put_image_to_image(frame, spr->image, location, spr->clips[i]);
		i++;
	}
}

int render_sprites(t_sprites *spr, t_image *frame)
{
	int	(*update)(t_sprites *spr);
	int	to_next;

	if (spr->delay > 0)
	{
		spr->timer++;
		if (spr->last_update == 0 \
			|| spr->timer - spr->last_update > spr->delay)
		{
			spr->last_update = spr->timer;
			update = spr->update;
			to_next = 1;
			if (update)
				to_next = update(spr);
			if (to_next == 1)
				spr->index = (spr->index + 1) % spr->max_index;
		}
	}
	render_sprites_utils(spr, frame);
	return (0);
}

int	load_sprites(t_sprites *spr)
{
	load_object(&spr->obj);
	ft_strlcpy((char *)spr, "sprites", NAME_SIZE);
	spr->obj.render = render_sprites;
	spr->update = NULL;
	spr->clips = NULL;
	spr->nb_clip = 0;
	spr->delay = 0;
	spr->last_update = 0;
	spr->timer = 0;
	return (0);	
}
