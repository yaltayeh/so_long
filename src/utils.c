/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:03:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 10:37:40 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_point	point_to_center(t_point center, t_point size)
{
	return ((t_point){center.x - size.x / 2, \
						center.y - size.y / 2});
}

int	load_image(struct s_image *img)
{
	img->buffer = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, \
									&img->size_line, &img->endian);
	if (!img->buffer)
		return (-1);
	return (0);
}
