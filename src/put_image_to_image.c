/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:22:42 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/01 09:00:10 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	blend_color(int a, int b)
{
	unsigned char	*ac;
	unsigned char	*bc;
	unsigned char	cc[4];
	unsigned char	alpha;

	ac = (unsigned char *)&a;
	bc = (unsigned char *)&b;
	alpha = bc[3];
	cc[0] = (ac[0] * alpha + (255 - alpha) * bc[0]) / 255;
	cc[1] = (ac[1] * alpha + (255 - alpha) * bc[1]) / 255;
	cc[2] = (ac[2] * alpha + (255 - alpha) * bc[2]) / 255;
	return (*(int *)cc);
}

void	put_image_to_image(t_image *dst, t_image *src, \
						int dest_x, int dest_y, t_clip clip)
{
	int	x;
	int	y;
	int	*dst_c;
	int	src_c;

	if (!dst || !src || !dst->buffer || !src->buffer \
			|| clip.height < 0 || clip.width < 0)
		return ;
	y = -1;
	while (++y < clip.height \
				&& y + clip.y < src->height \
				&& y + dest_y < dst->height)
	{
		if (y + clip.y < 0 || y + dest_y < 0)
			continue ;
		x = -1;
		while (++x < clip.width && x + clip.x < src->width \
								&& x + dest_x < dst->width)
		{
			if (x + clip.x < 0 || x + dest_x < 0)
				continue ;
			dst_c = &dst->buffer[(y + dest_y) * dst->width + (x + dest_x)];
			src_c = src->buffer[(y + clip.y) * src->width + (x + clip.x)];
			*dst_c = blend_color(*dst_c, src_c);
		}
	}
}