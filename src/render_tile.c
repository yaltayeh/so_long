/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/02 11:50:06 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    render_tile(t_mlx_data *ctx, t_image *bg)
{
    char map[8][8] = {
		"11111111",
		"11111111",
		"11000011",
		"11000011",
		"11000011",
		"11000011",
		"11111111",
		"11111111"
	};

	int	points[8][2] = {
		{-1,0},
		{1,-1},
		{0,1},
		{0,-1},
		{1,1},
		{1,0},
		{-1,-1},
		{-1,1},
	};
    for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
        {
            if (map[y][x] == '1')
			{
                int num = 0;
                for (int i = 0; i < 8; i++)
                {
					int _x, _y;
					_x = x + points[i][0];
					_y = y + points[i][1];
                    num <<= 1;
                    if (_x < 0 || _x >= 8 || _y < 0 || _y >= 8)
							continue;
                    if (map[_y][_x] == '0')
                        num |= 1;
                }
				if 		(num & 1 << 4)
				{
					put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].edges[1]);
					put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].edges[2]);
				}
				else if (num & 1 << 5)
				{
					put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].edges[1]);
					put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].edges[2]);
				}
				else if (num & 1 << 6)
				{
					put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].edges[2]);
					put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].edges[1]);
				}
				else if (num & 1 << 7)
				{
					put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].edges[3]);
					put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].edges[0]);
				}
				// else if (num & 1 << 7)
				// {
				// 	put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].outer_corners[3]);
				// 	put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].inner_corners[3]);
				// }
				// else if (num & 1 << 5)
				// {
				// 	put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].outer_corners[2]);
				// 	put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].inner_corners[2]);
				// }
				// else if (num & 1 << 2)
				// {
				// 	put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].outer_corners[1]);
				// 	put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].inner_corners[1]);
				// }
				// else if (num & 1 << 0)
				// {
				// 	put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[1].outer_corners[0]);
				// 	put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].inner_corners[0]);
				// }
				else
					put_image_to_image(bg, &ctx->tiles[1].img, 32 * x, 32 * y, ctx->tiles[1].main_tile);
            }
			else if (map[y][x] == '0')
				put_image_to_image(bg, &ctx->tiles[0].img, 32 * x, 32 * y, ctx->tiles[0].main_tile);
		}
	}
}