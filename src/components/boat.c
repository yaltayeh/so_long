/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:26:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/11 23:14:48 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

int	animate_boat(t_boat *boat)
{
	boat->clip = (t_clip){boat->spr.index * 64, boat->direction * 64, 64, 64};
	return (1);
}

int	load_boat(t_boat *boat, t_game_schema *gs)
{
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
	return (0);
}