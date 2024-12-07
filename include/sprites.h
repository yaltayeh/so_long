/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:09:12 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 08:29:58 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "object.h"

typedef struct s_sprites
{
	t_object	obj;
	t_image		image;
	int			col;
	int			max_col;
	t_clip		*clip;
	int			(*update)();
	t_clock		last_update;
	t_clock		delay;
	t_clock		timer;
}	t_sprites;

int	load_sprites(t_sprites *spr, void *mlx_ptr, char *spr_path);
int	render_sprites(t_sprites *spr, t_image *frame);

#endif