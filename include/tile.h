/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:49:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 07:32:25 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_H
# define TILE_H

# include "sprites.h"
# include "object.h"
# include "schema.h"
# include "config.h"

typedef struct s_floor
{
	t_sprites	spr;
	int			size;

	t_clip		tileds[16];
	t_clip		big_spot;
	t_clip		small_spot;
}	t_floor;

typedef struct s_tile
{
	t_sprites	spr;
}	t_tile;

int	load_floor(t_floor *f, int size);

int	load_tile(t_tile *tile, t_schema *schema, \
				t_clip *clip, t_object *parent);

#endif