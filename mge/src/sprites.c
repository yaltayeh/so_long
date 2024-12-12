/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:57:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/12 17:57:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"
#include <stdio.h>


void	animate_sprites(void *_spr)
{
	t_sprites	*spr;
	void		(*animate)(t_sprites *);

	spr = (t_sprites *)_spr;
	if (spr->delay > 0)
	{
		spr->timer++;
		if (spr->last_animate == 0 \
			|| spr->timer - spr->last_animate > spr->delay)
		{
			spr->last_animate = spr->timer;
			animate = spr->animate;
			if (animate)
				animate(spr);
			if (spr->max_index > 0)
				spr->index = (spr->index + 1) % spr->max_index;
		}
	}
}

int	render_sprites(void *_spr, t_image *frame)
{
	t_sprites	*spr;
	int			i;

	spr = (t_sprites *)_spr;
	update_object(spr);
	animate_sprites(spr);
	i = 0;
	while (spr->clips && i < spr->nb_clip)
	{
		put_image_to_image(frame, spr->image, spr->obj.absolute_location, spr->clips[i]);
		i++;
	}
	return (0);
}

int	load_sprites(void *_spr)
{
	t_sprites	*spr;

	spr = (t_sprites *)_spr;
	load_object(spr);
	ft_strlcpy((char *)spr, "sprites", NAME_SIZE);
	spr->obj.render = render_sprites;
	spr->animate = NULL;
	spr->clips = NULL;
	spr->nb_clip = 0;
	spr->delay = 0;
	spr->run_animate = 1;
	spr->last_animate = 0;
	spr->timer = 0;
	return (0);
}
