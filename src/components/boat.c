/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:26:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 10:02:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

void	animate_boat(t_boat *boat)
{
	boat->clip = (t_clip){boat->spr.index * 64, \
							boat->direction * 64, \
								64, 64, 0};
}

t_boat	*init_boat(t_game_schema *gs)
{
	t_boat	*boat;

	boat = malloc(sizeof(t_boat));
	if (!boat)
		return (NULL);
	load_sprites((void *)boat);
	ft_strlcpy((char *)boat, "boat", NAME_SIZE);
	((t_object *)boat)->center_point = (t_point){32, 32};
	((t_object *)boat)->destroy = defult_destroy_object;
	((t_sprites *)boat)->image = schema_get_image_by_name(gs, "boat");
	((t_sprites *)boat)->clips = &boat->clip;
	((t_sprites *)boat)->index = 0;
	((t_sprites *)boat)->max_index = 4;
	((t_sprites *)boat)->nb_clips = 1;
	((t_sprites *)boat)->delay = 3;
	((t_sprites *)boat)->animate = animate_boat;
	boat->direction = DIAGONAL;
	return (boat);
}
