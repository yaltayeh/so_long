/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:26:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/13 16:18:20 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

void	animate_boat(t_boat *boat)
{
	boat->clip = (t_clip){boat->spr.index * 64, boat->direction * 64, 64, 64, 1};
}

t_boat	*init_boat(t_game_schema *gs)
{
	t_boat	*boat;
	
	boat = malloc(sizeof(t_boat));
	if (!boat)
		return (NULL);
	load_sprites((void *)boat);
	ft_strlcpy((char *)boat, "boat", NAME_SIZE);
	boat->spr.obj.center_point = (t_point){32, 32};
	boat->spr.image = schema_get_image_by_name(gs, "boat");
	boat->spr.clips = &boat->clip;
	boat->spr.index = 0;
	boat->spr.max_index = 4;
	boat->spr.nb_clip = 1;
	boat->spr.delay = BOAT_DELEY;
	boat->direction = DIAGONAL;
	boat->spr.animate = animate_boat;
	boat->spr.obj.destroy = defult_destroy_object;
	return (boat);
}