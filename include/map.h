/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:57:34 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/29 11:56:42 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "sprites.h"
# include "schema.h"
# include "config.h"

typedef struct s_tile
{
	t_sprites	spr;
}	t_tile;

typedef struct s_grid
{
	char	**blocks;
	int		rows;
	int		cols;
}	t_grid;

typedef struct s_map
{
	t_sprites	spr;
	t_clip		tileds[16];
	t_clip		big_spot;
	t_clip		small_spot;
	t_grid		o_grid;
	t_grid		s_grid;
	t_grid		p_grid;
	int			nb_collect;
}	t_map;

void	load_map(t_map *map);
int		open_map_and_check(t_map *map, const char *map_path);

int		init_tiles(t_map *map, void *schema);

t_clip	*get_tile_clip(t_map *map, t_grid *grid, int r, int c);

int		scale_x2_grid(t_grid *dst, t_grid *src);
int		copy_grid(t_grid *dst, t_grid *src);
int		free_grid(t_grid *grid);
int	scale_grid(t_grid *o_map, int r, int c);


int		print_error_line(char **lines, int line_no, int char_no, char *msg);
int		print_error_number1(t_grid *grid, int *nb);
int		print_error_number2(t_grid *p_grid, t_grid *o_grid, int *nb);

#endif
