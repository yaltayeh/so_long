/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 07:00:09 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/02 11:47:12 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <libft.h>
# include <mlx.h>

# define NAME_SIZE 16

typedef unsigned long		t_clock;

typedef struct s_image
{
	char	name[NAME_SIZE];
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

typedef struct s_cell
{
	int	r;
	int	c;
}	t_cell;

typedef struct s_clip
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	layer;
}	t_clip;

t_point	point_to_center(t_point center, t_point size);
int		load_image_data(t_image *img);

void	put_image_to_image(t_image *dst, t_image *src, \
						t_point dst_loc, t_clip clip);

t_point	add_point(t_point p1, t_point p2);

int		is_new_movement(t_point old_location, t_point new_location);

#endif