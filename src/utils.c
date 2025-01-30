/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:03:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 12:11:40 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_point	point_to_center(t_point center, t_point size)
{
	return ((t_point){center.x - size.x / 2, \
						center.y - size.y / 2});
}

int	load_image_data(struct s_image *img)
{
	img->buffer = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, \
									&img->size_line, &img->endian);
	if (!img->buffer)
		return (-1);
	return (0);
}

t_point	add_point(t_point p1, t_point p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	return (p1);
}

int ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}