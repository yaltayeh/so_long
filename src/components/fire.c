/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:01:22 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/08 14:27:22 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

static int	update_fire(t_fire *fire)
{
	fire->clips[0] = (t_clip){fire->spr.index * 132, 92, 132, 92};
	fire->clips[1] = (t_clip){fire->spr.index * 132, 0, 132, 92};
	return (1);
}

int	load_fire(t_fire *fire, t_components *components)
{
	load_sprites((void *)fire, NULL, NULL);
	fire->spr.obj.center_point = (t_point){66, 46};
	fire->spr.image = components->images[FIRE];
	fire->spr.index = 0;
	fire->spr.max_index = 6;
	fire->spr.clips = fire->clips;
	fire->spr.nb_clip = 2;
	fire->spr.delay = FIRE_DELEY;
	fire->spr.update = update_fire;
	return (0);
}