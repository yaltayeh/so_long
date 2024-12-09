/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiled.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:49:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 14:10:06 by yaltayeh         ###   ########.fr       */
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

	t_clip		main_tile;
	t_clip		small_spot;
	t_clip		big_spot;
	t_clip		inner_corners[4];
	t_clip		outer_corners[4];
	t_clip		edges[4];
	t_clip		alternate[3];
}	t_tiled_data;

typedef t_sprites	t_tiled;

int	load_tiled_data(t_tiled_data *t, int size);

int	load_tiled(t_tiled *tiled, t_schema *schema, t_clip *clip);

#endif