/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:25:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 10:20:34 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"

static t_clip	get_number_clip(int digit)
{
	return ((t_clip){digit * 15, 0, 15, 32, 2});
}

static void	set_clips_value(int number, t_clip *clips, int nb_clips)
{
	if (nb_clips <= 0)
		return ;
	if (number < 10)
	{
		*clips = get_number_clip(number);
	}
	else
	{
		set_clips_value(number / 10, clips + 1, nb_clips - 1);
		set_clips_value(number % 10, clips, nb_clips);
	}
}

static void	animate_banner(t_banner *banner)
{
	set_clips_value(*banner->logs_collected, banner->clips + 2, 5);
	set_clips_value(*banner->movement, banner->clips + 9, 5);
}

int	load_banner(t_banner *banner, t_game_schema *gs)
{
	t_player	*player;

	load_object(banner);
	ft_bzero(banner, sizeof(*banner));
	ft_strlcpy((char *)banner, "banner", NAME_SIZE);
	
	player = get_children_by_name(&gs->components, "player");
	
	((t_object *)banner)->render = animate_banner;
	
	banner->image = schema_get_image_by_name(gs, "banner");
	banner->logs_collected = &player->logs_count;
	banner->nb_collect = gs->map.nb_collect;
	banner->movement = 0;
	
}