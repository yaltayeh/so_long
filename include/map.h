/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:57:34 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 12:08:59 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "tile.h"
# include "components.h"

typedef struct s_grid
{
	char	**blocks;
	int		rows;
	int		cols;
}	t_grid;

typedef struct s_map
{
	t_floor	floor;
	t_grid	o_grid; // orginal grid
	t_grid	s_grid; // scaled grid
	t_grid	p_grid; // path grid
	t_tile	*tiles;
	int		nb_tiles;
	int		nb_collect;
}	t_map;

int	map_parser(t_map *map, const char *map_path);
int	load_map(t_map *map, const char *grid_path);
int	init_tiles(t_tile **tileds_r, t_grid *s_map, \
						t_floor *t, void *schema);

t_clip	*get_tile_clip(t_grid *map, t_floor *t, int r, int c);


int	scale_grid(t_grid *dst, t_grid *src);
int	copy_grid(t_grid *dst, t_grid *src);

int	print_error_line(char **lines, int line_no, int char_no, char *msg);
int	print_error_number1(t_grid *grid, int *nb);
int	print_error_number2(t_grid *p_grid, t_grid *o_grid, int *nb);

#endif
