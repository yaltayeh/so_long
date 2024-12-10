/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:01:22 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/10 07:31:17 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

static int	update_fire(t_fire *fire)
{
	fire->clips[0] = (t_clip){fire->spr.index * 132, 92, 132, 92};
	fire->clips[1] = (t_clip){fire->spr.index * 132, 0, 132, 92};
	return (1);
}

int	load_fire(t_fire *fire, void *schema)
{
	load_sprites((void *)fire);
	ft_strlcpy((char *)fire, "fire", NAME_SIZE);
	fire->spr.obj.center_point = (t_point){66, 46};
	fire->spr.image = schema_get_image_by_name(schema, "fire");
	fire->spr.index = 0;
	fire->spr.max_index = 6;
	fire->spr.clips = fire->clips;
	fire->spr.nb_clip = 2;
	fire->spr.delay = FIRE_DELEY;
	fire->spr.update = update_fire;
	return (0);
}