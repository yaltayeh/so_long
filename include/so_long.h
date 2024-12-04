/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:36:48 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/04 12:10:13 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <ft_stack.h>
# include <fcntl.h>
# include "utility.h"

# define BLOCK_SIZE 64

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

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	
	int				width;
	int				height;
	
	struct s_map	map;
	struct s_map	scaled_map;

	// t_object		*player;
	t_tile			tiles[3];
	
	t_clock			last_rander;
	t_clock			time;

}	t_game;


void *destroy_object(t_object	**obj);
t_sprite	*init_character(void *mlx_ptr, char *sprites_path);

int map_parser(const char *map_path, t_game *game);

int	**convert_map_to_2d_array(t_stack *map);

int	load_image(t_image *img);

t_tile	xpm_file_to_tile(char *tile_path, t_game *game);

void	put_image_to_image(t_image *dst, t_image *src, \
						int dest_x, int dest_y, t_clip clip);

void	load_tile_data(t_tile *tile, int index);

void    render_tile(t_game *game, t_image *bg);


#endif
