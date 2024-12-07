/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:57:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 18:17:45 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"
#include <stdio.h>
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
				spr->col = (spr->col + 1) % spr->max_col;
		}
	}
	if (!spr->clip)
		return (0);
	// free(malloc(0));
	put_image_to_image(frame, &spr->image, spr->obj.loc, *spr->clip);
	return (0);
}

int	load_sprites(t_sprites *spr, void *mlx_ptr, char *spr_path)
{
	load_object(&spr->obj, mlx_ptr);
	spr->obj.render = render_sprites;
	spr->update = NULL;
	spr->clip = NULL;
	spr->delay = 0;
	spr->last_update = 0;
	spr->timer = 0;
	if (spr_path)
	{
		spr->image.img_ptr = mlx_xpm_file_to_image(mlx_ptr, spr_path, 
									&spr->image.width, &spr->image.height);
		if (!spr->image.img_ptr)
			return (-1);
		if (load_image(&spr->image) == -1)
			return (-1);
	}
	return (0);	
}
