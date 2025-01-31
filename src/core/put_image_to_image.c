/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:22:42 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/31 09:31:15 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	blend_color(int c1, int c2)
{
	unsigned char	*_c1;
	unsigned char	*_c2;
	unsigned char	c3[4];
	unsigned char	alpha;

	_c1 = (unsigned char *)&c1;
	_c2 = (unsigned char *)&c2;
	alpha = _c2[3];
	c3[0] = (_c1[0] * alpha + (255 - alpha) * _c2[0]) / 255;
	c3[1] = (_c1[1] * alpha + (255 - alpha) * _c2[1]) / 255;
	c3[2] = (_c1[2] * alpha + (255 - alpha) * _c2[2]) / 255;
	return (*(int *)c3);
}

void	put_image_to_image(t_image *dst, t_image *src, \
						t_point dst_loc, t_clip clip)
{
	int	x;
	int	y;
	int	*dc;
	int	sc;

	if (!dst || !src || !dst->buffer || !src->buffer \
			|| clip.height < 0 || clip.width < 0)
		return ;
	y = -1;
	while (++y < clip.height && y + clip.y < src->height \
								&& y + dst_loc.y < dst->height)
	{
		if (y + clip.y < 0 || y + dst_loc.y < 0)
			continue ;
		x = -1;
		while (++x < clip.width && x + clip.x < src->width \
								&& x + dst_loc.x < dst->width)
		{
			if (x + clip.x < 0 || x + dst_loc.x < 0)
				continue ;
			dc = &dst->buffer[(y + dst_loc.y) * dst->width + (x + dst_loc.x)];
			sc = src->buffer[(y + clip.y) * src->width + (x + clip.x)];
			*dc = blend_color(*dc, sc);
		}
	}
}
