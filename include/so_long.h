/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:36:48 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/02 10:33:01 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <libft.h>
# include <ft_stack.h>
# include <fcntl.h>
# include <sys/time.h>

#ifdef __linux__
# define DELAY		12500
# define KEY_UP		XK_Up
# define KEY_DOWN	XK_Down
# define KEY_RIGHT	XK_Right
# define KEY_LEFT	XK_Left
#else
# define DELAY		1100
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_RIGHT	124
# define KEY_LEFT	123
#endif

// Mouse button codes
#define LEFT_CLICK 1
#define RIGHT_CLICK 2

#define ESC_KEYCODE 53


enum e_error_code
{
	SUCCESS,
	MAP_RECTANGULAR,
	MAP_SURROUNDED,
	FILE_OPEN,
	CHARACTER,
	MALLOC,
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

typedef struct s_clip
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_clip;


typedef struct s_tile
{
	struct s_image	img;
	struct s_clip	main_tile;
	struct s_clip	small_spot;
	struct s_clip	big_spot;
	struct s_clip	inner_corners[4];
	struct s_clip	outer_corners[4];
	struct s_clip	edges[4];
	struct s_clip	alternate[3];
}	t_tile;


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
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
	struct s_map
	{
		char	**map;
		int		rows;
		int		cols;
	}	map;

	t_2d_object		*player;
	clock_t			last_rander;
	clock_t			time;

	t_tile	tiles[3];
}	t_mlx_data;


void *destroy_object(t_2d_object	**obj);
t_2d_object	*init_character(void *mlx_ptr, char *sprites_path);

int map_parser(const char *map_path, t_mlx_data *ctx);

int	**convert_map_to_2d_array(t_stack *map);

int	load_image(struct s_image *img);

t_tile	xpm_file_to_tile(char *tile_path, t_mlx_data *ctx);

void	put_image_to_image(t_image *dst, t_image *src, \
						int dest_x, int dest_y, t_clip clip);

void    render_tile(t_mlx_data *ctx, t_image *bg);

#endif
