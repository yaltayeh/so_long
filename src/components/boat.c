/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:26:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 08:28:47 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

int	update_boat(t_boat *boat)
{

}

int	load_boat(t_boat *boat, t_components *components)
{
	load_sprites((void *)boat, NULL, NULL);
	boat->spr.image = components->images[BOAT];
	boat->spr.clip = &boat->clip;
	boat->spr.col = 0;
	boat->spr.max_col = 4;
	boat->spr.delay = BOAT_DELEY;
	boat->spr.update = update_boat;
	return (0);
}