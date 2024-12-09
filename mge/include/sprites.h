/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:09:12 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 13:27:16 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "object.h"

typedef struct s_sprites
{
	t_object	obj;
	t_image		*image;

	int			index;
	int			max_index;

	t_clip		*clips;
	int			nb_clip;

	t_clock		last_update;
	t_clock		delay;
	t_clock		timer;

	int			(*update)();
}	t_sprites;

int	load_sprites(t_sprites *spr);
int	render_sprites(t_sprites *spr, t_image *frame);

#endif