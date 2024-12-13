/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiled.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:49:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/13 14:52:54 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILED_H
# define TILED_H

# include "sprites.h"
# include "mge.h"
# include "config.h"

typedef struct s_tiled_data
{
	t_sprites	spr;
	int			size;

	t_clip		tileds[16];
	t_clip		big_spot;
	t_clip		small_spot;
}	t_tiled_data;

typedef struct s_tiled
{
	t_sprites	spr;
}	t_tiled;

int	load_tiled_data(t_tiled_data *t, int size);

int	load_tiled(t_tiled *tiled, t_schema *schema, \
				t_clip *clip, t_object *parent);

#endif