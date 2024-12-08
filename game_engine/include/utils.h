/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 07:00:09 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 10:09:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <mlx.h>
# include <stdlib.h>
# include <libft.h>
# include "config.h"

typedef unsigned long	t_clock;

typedef struct s_image
{
	void	*img_ptr;
	int		*buffer;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_clip
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_clip;

t_point	point_to_center(t_point center, t_point size);

int	load_image(t_image *img);

void	put_image_to_image(t_image *dst, t_image *src, \
						t_point dst_loc, t_clip clip);

#endif