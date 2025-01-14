/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:57:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/13 17:22:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"
#include <stdio.h>

void	animate_sprites(void *_spr)
{
	t_sprites	*spr;
	void		(*animate)(t_sprites *);
	void		(*end_move)(t_sprites *);

	spr = (t_sprites *)_spr;
	if (spr->delay > 0 && spr->run_animate)
	{
		animate = spr->animate;
		end_move = spr->end_move;
		spr->timer++;
		if (spr->last_animate == 0 \
			|| spr->timer - spr->last_animate > spr->delay)
		{
			spr->last_animate = spr->timer;
			if (animate)
				animate(spr);
			if (spr->max_index > 0)
				spr->index = (spr->index + 1) % spr->max_index;
			if (spr->index == 0)
				if (end_move)
					end_move(spr);
		}
	}
}

int	render_sprites(void *_spr, t_image *frame, int layer)
{
	t_sprites	*spr;
	int			i;

	spr = (t_sprites *)_spr;
	if (layer == 0)
	{
		update_object(spr);
		animate_sprites(spr);
	}
	i = 0;
	while (spr->clips && i < spr->nb_clip)
	{
		if (spr->clips[i].layer == layer)
			put_image_to_image(frame, spr->image, \
						spr->obj.absolute_location, spr->clips[i]);
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
	spr->clips = NULL;
	spr->nb_clip = 0;
	spr->delay = 0;
	spr->run_animate = 1;
	spr->last_animate = 0;
	spr->timer = 0;
	spr->index = 0;
	spr->max_index = 0;
	spr->obj.render = render_sprites;
	spr->animate = NULL;
	spr->end_move = NULL;
	return (0);
}
