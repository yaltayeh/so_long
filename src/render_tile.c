/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/04 11:00:29 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void 	put_tile_to_image(t_image *img, t_tile *tile, int x, int y, int i, int num)
{
	t_image	*tile_img;

	tile_img = &tile->sprite.image;
	i /= 2;
	if (num == 1)
		put_image_to_image(img, tile_img, x, y, tile->outer_corners[(i + 3) % 4]);
	if (num == 7 || num == 3)
		put_image_to_image(img, tile_img, x, y, tile->edges[(i + 1) % 4]);
	if (num == 31 || num == 15 || num == 27)
		put_image_to_image(img, tile_img, x, y, tile->inner_corners[i % 4]);
	if (num == 99)
		put_image_to_image(img, tile_img, x, y, tile->inner_corners[(i + 1) % 4]);
}

void    render_tile(t_game *ctx, t_image *bg)
{
	struct s_map *map;

	map = &ctx->scaled_map;
	int	points[8][2] = {
		{-1,-1}, {0,-1}, {1,-1}, {1,0},
		{1,1},   {0,1},  {-1,1}, {-1,0},
	};
    for (int y = 0; y < map->rows; y++)
	{
		for (int x = 0; x < map->cols; x++)
        {
            if (map->map[y][x] == '1')
			{
                unsigned char num = 0;
                for (int i = 0; i < 8; i++)
                {
					int _x, _y;
					_x = x + points[i][0];
					_y = y + points[i][1];
                    num <<= 1;
                    if (_x < 0 || _x >= map->cols || _y < 0 || _y >= map->rows)
							continue;
                    if (map->map[_y][_x] == '0')
                        num |= 1;
                }
				if (!num)
					put_image_to_image(bg, &ctx->tiles[0].sprite.image, BLOCK_SIZE * x, BLOCK_SIZE * y, ctx->tiles[0].alternate[1]);
				else
				{
					int i = 0;
					while (!(num >> 7 != 1 && num & 1))
					{
						num = num << 1 | num >> 7;
						i++;
					}
					// ft_printf("%d.", i);
					put_tile_to_image(bg, &ctx->tiles[0], BLOCK_SIZE * x, BLOCK_SIZE * y, i, num);
				}
				// ft_printf("%-3d ", num);
            }
			else if (map->map[y][x] == '0')
			{
				// ft_printf("%3d ", map->map[y][x]);
				put_image_to_image(bg, &ctx->tiles[0].sprite.image, BLOCK_SIZE * x, BLOCK_SIZE * y, ctx->tiles[0].main_tile);
			}
		}
		// ft_printf("\n");
	}
	// ft_printf("\n");
}
