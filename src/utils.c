/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:03:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/02 11:38:23 by yaltayeh         ###   ########.fr       */
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

int	is_new_movement(t_point old_location, t_point new_location)
{
	old_location.x /= 128;
	old_location.y /= 128;
	new_location.x /= 128;
	new_location.y /= 128;
	if (ft_memcmp(&old_location, &new_location, sizeof(t_point)) == 0)
		return (0);
	return (1);
}
