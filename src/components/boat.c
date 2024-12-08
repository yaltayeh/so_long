/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:26:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/08 08:35:29 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

int	update_boat(t_boat *boat)
{
	boat->clip = (t_clip){boat->spr.col * 64, boat->direction * 64, 64, 64};
	return (1);
}

int	load_boat(t_boat *boat, t_components *components)
{
	load_sprites((void *)boat, NULL, NULL);
	boat->spr.obj.center_point = (t_point){32, 32};
	boat->spr.image = components->images[BOAT];
	boat->spr.clip = &boat->clip;
	boat->spr.col = 0;
	boat->spr.max_col = 4;
	boat->spr.nb_clip = 1;
	boat->spr.delay = BOAT_DELEY;
	boat->direction = DIAGONAL;
	boat->spr.update = update_boat;
	return (0);
}