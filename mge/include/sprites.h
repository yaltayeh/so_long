/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:09:12 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/13 11:58:55 by yaltayeh         ###   ########.fr       */
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

	int			run_animate;
	t_clock		last_animate;
	t_clock		delay;
	t_clock		timer;

	void			(*animate)();
}	t_sprites;

int		load_sprites(void *_spr);
int		render_sprites(void *_spr, t_image *frame, int layer);
void	animate_sprites(void *_spr);

#endif