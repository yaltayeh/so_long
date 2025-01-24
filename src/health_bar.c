/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:02:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/24 20:40:27 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "health_bar.h"

void    health_bar_animate(t_health_bar *health_bar)
{
    // ((t_object *)health_bar)->center_point = {0, 16 * 1};
}

int load_health_bar(void *schema, t_health_bar *health_bar, \
                    int *health_r, int health_bar_type)
{
    if (load_sprites(health_bar) != 0)
        return (-1);
    health_bar->spr.image = schema_get_image_by_name(schema, "health_bar");
    health_bar->spr.clips = &health_bar->clip;
    health_bar->spr.nb_clip = 1;
    health_bar->spr.animate = health_bar_animate;
}
