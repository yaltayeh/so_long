/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:57:34 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/10 11:03:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "tiled.h"
# include "components.h"

# define COMPONENTS_CHARACTERS "PECF" 
# define MAP_CHARACTERS "01PECF"

typedef struct s_map_data
{
	char	**blocks;
	int		rows;
	int		cols;
}	t_map_data;

typedef struct s_map
{
	t_tiled_data	tiled_data;
	t_map_data		o_map;
	t_map_data		s_map;
	t_tiled			*tileds;
	int				nb_tileds;
}	t_map;

int	map_parser(t_map_data *map, const char *map_path);
int	load_map(t_map *map, const char *map_path);
int	scale_map(t_map_data *dst, t_map_data *src);
int	init_tiled_blocks(t_tiled **tileds_r, t_map_data *s_map, \
						t_tiled_data *t, void *schema);

#endif
