/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:25:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 13:34:16 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"

static t_clip	get_digit_clip(int digit)
{
	return ((t_clip){digit * 15, 0, 15, 32, 2});
}

static int	digit_count(unsigned int number)
{
	int	nb;

	if (number == 0)
		return (1);
	nb = 0;
	while (number)
	{
		number /= 10;
		nb++;
	}
	return (nb);
}

static void	put_digits(t_banner *banner, t_image *frame, \
						unsigned int number, t_point offset)
{
	t_clip	clip;
	t_point	cursor;
	int		nb;

	nb = digit_count(number);
	cursor = (t_point){(nb - 1) * 15 + ((5 - nb) * 15) / 2, 0};
	cursor = add_point(cursor, offset);
	while (nb)
	{
		offset = cursor;
		clip = get_digit_clip(number % 10);
		offset = add_point(offset, banner->obj.absolute_location);
		offset = add_point(offset, (t_point){32, 0});
		put_image_to_image(frame, banner->image, offset, clip);
		cursor.x -= 15;
		number /= 10;
		nb--;
	}
}

static int	render_banner(t_banner *banner, t_image *frame, int layer)
{
	t_clip	dst_clip;
	t_point	offset = (t_point){4 * 32, 32 * 0};

	if (layer != 2)
		return 0;
	dst_clip = (t_clip){offset.x + 15 * 11, offset.y, 4 * 32, 32, 2};
	
	// put banner
	put_image_to_image(frame, banner->image, \
			banner->obj.absolute_location, \
			dst_clip);
	put_image_to_image(frame, banner->image, \
			add_point(banner->obj.absolute_location, (t_point){0, 32 + 8}), \
			dst_clip);
	
	put_digits(banner, frame, *banner->logs_collected, (t_point){10, 0});
	put_digits(banner, frame, *banner->movement, (t_point){10, 32 + 8});
	
	// set_clips_value(*banner->logs_collected, banner->clips + 2, 5);
	// ft_printf("%s movement: %d, logs: %d\n", __func__, *banner->movement, *banner->logs_collected);
	// set_clips_value(*banner->movement, banner->clips + 9, 5);

	return (0);
}

void	load_banner(t_banner *banner, t_game_schema *gs)
{
	t_player	*player;

	load_object(banner);
	ft_bzero(banner, sizeof(*banner));
	ft_strlcpy((char *)banner, "banner", NAME_SIZE);
	
	player = (t_player *)get_children_by_name(&gs->components, "player");
	((t_object *)banner)->relative_location = (t_point){10, 10};
	((t_object *)banner)->render = render_banner;
	
	banner->image = schema_get_image_by_name(gs, "banner");
	banner->logs_collected = &player->logs_count;
	banner->movement = &player->nb_movement;
}