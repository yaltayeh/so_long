/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:25:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/15 18:48:30 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"

int banner_render(t_banner *banner, t_image *frame)
{
	
}

int	load_banner(t_banner *banner, t_game_schema *gs)
{
	banner->logs_collected = 0;
	banner->nb_collect = gs->map.nb_collect;
	((t_object *)banner)->render = banner_render;
}