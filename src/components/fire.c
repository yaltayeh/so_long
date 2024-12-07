/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:01:22 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 10:02:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

static int	render_fire(t_fire *fire, t_image *frame)
{
	t_clip	light_clip;
	t_clip	fire_clip;

	light_clip = (t_clip){fire->col * 132, 92, 132, 92};
	fire_clip = (t_clip){fire->col * 132, 0, 132, 92};
	
	put_image_to_image(frame, &fire->image, fire->obj.loc, light_clip);
	put_image_to_image(frame, &fire->image, fire->obj.loc, fire_clip);
	if (render_sprites(fire, frame) != 0)
		return (-1);
	return (0);
}

int	load_fire(t_fire *fire, t_components *components)
{
	load_sprites((void *)fire, NULL, NULL);
	fire->image = components->images[FIRE];
	fire->col = 0;
	fire->max_col = 6;
	fire->delay = FIRE_DELEY;
	fire->obj.render = render_fire;
	return (0);
}