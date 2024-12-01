/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:27:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/01 14:16:29 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_tile_data(t_tile *tile)
{
	tile->big_spot = (struct s_clip){0, 0, 32, 32};
	tile->small_spot = (struct s_clip){0, 32, 32, 32};
	tile->inner_corners[0] = (struct s_clip){32, 0, 32, 32};
	tile->inner_corners[1] = (struct s_clip){64, 0, 32, 32};
	tile->inner_corners[2] = (struct s_clip){32, 32, 32, 32};
	tile->inner_corners[3] = (struct s_clip){64, 32, 32, 32};
	tile->outer_corners[0] = (struct s_clip){0, 64, 32, 32};
	tile->outer_corners[1] = (struct s_clip){64, 64, 32, 32};
	tile->outer_corners[2] = (struct s_clip){0, 128, 32, 32};
	tile->outer_corners[3] = (struct s_clip){64, 128, 32, 32};
	tile->edges[0] = (struct s_clip){32, 64, 32, 32};
	tile->edges[1] = (struct s_clip){0, 96, 32, 32};
	tile->edges[2] = (struct s_clip){64, 96, 32, 32};
	tile->edges[3] = (struct s_clip){32, 128, 32, 32};
	tile->alternate[0] = (struct s_clip){0, 160, 32, 32};
	tile->alternate[1] = (struct s_clip){32, 160, 32, 32};
	tile->alternate[2] = (struct s_clip){64, 160, 32, 32};
	tile->main_tile = (struct s_clip){32, 96, 32, 32};
}

t_tile	xpm_file_to_tile(char *tile_path, t_mlx_data *ctx)
{
	t_tile	tile;

	load_tile_data(&tile);
	tile.img.img_ptr = mlx_xpm_file_to_image(ctx->mlx_ptr, tile_path, \
										&tile.img.width, &tile.img.height);
	if (!tile.img.img_ptr)
		return (tile);
	load_image(&tile.img);
	return (tile);
}
