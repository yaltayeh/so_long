/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 07:00:09 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/04 10:56:42 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

typedef unsigned long t_clock;

enum directions
{
	BACK,
	LEFT,
	FRONT,
	RIGHT
};

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

typedef struct s_object
{
	t_point	loc;
	void	*mlx_ptr;
	int		(*render)(struct s_object *obj);
	t_clock	deley;
	t_clock	last_render;
}	t_object;

typedef struct s_sprite
{
	struct s_object	obj;
	struct s_image	image;
	int				row;
	int				col;
	int				r;
	int				c;
}	t_sprite;

typedef struct s_tile
{
	struct s_sprite	sprite;
	struct s_clip	main_tile;
	struct s_clip	small_spot;
	struct s_clip	big_spot;
	struct s_clip	inner_corners[4];
	struct s_clip	outer_corners[4];
	struct s_clip	edges[4];
	struct s_clip	alternate[3];
}	t_tile;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
}	t_map;

int		scale_map(t_map *dst, t_map *src);

#endif