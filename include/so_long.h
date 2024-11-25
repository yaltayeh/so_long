/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:36:48 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/25 19:46:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

// Mouse button codes
#define LEFT_CLICK 1
#define RIGHT_CLICK 2

#define ESC_KEYCODE 53

struct s_image
{
	int		bpp;
	int		size_line;
	int		endian;
	int		*buffer;
	void	*img_ptr;
	int		width;
	int		height;
};

enum directions
{
	BACK,
	LEFT,
	FRONT,
	RIGHT
};

typedef struct s_sprites
{
	enum directions directions[4];
} t_sprites;

typedef struct s_2d_object
{
	void	*mlx_ptr;

	struct s_image object;
	struct s_image sprites;

	int		row;
	int		col;
	int		r;
	int		c;
}	t_2d_object;


typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	t_2d_object	*player_character;
}	t_mlx_data;


void *destroy_object(t_2d_object	**obj);
t_2d_object	*init_character(void *mlx_ptr, char *sprites_path);

#endif