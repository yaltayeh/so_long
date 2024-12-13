/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:01:22 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/13 16:17:33 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

static void	animate_fire(t_fire *fire)
{
	fire->clips[0] = (t_clip){fire->spr.index * 132, 92, 132, 92, 0};
	fire->clips[1] = (t_clip){fire->spr.index * 132, 0, 132, 92, 1};
}

t_fire	*init_fire(t_game_schema *gs)
{
	t_fire	*fire;

	fire = malloc(sizeof(t_fire));
	if (!fire)
		return (NULL);
	load_sprites((void *)fire);
	ft_strlcpy((char *)fire, "fire", NAME_SIZE);
	fire->spr.obj.center_point = (t_point){66, 46};
	fire->spr.image = schema_get_image_by_name(gs, "fire");
	fire->spr.index = 0;
	fire->spr.max_index = 6;
	fire->spr.clips = fire->clips;
	fire->spr.nb_clip = 2;
	fire->spr.delay = FIRE_DELEY;
	fire->spr.animate = animate_fire;
	fire->spr.obj.destroy = defult_destroy_object;
	return (fire);
}
