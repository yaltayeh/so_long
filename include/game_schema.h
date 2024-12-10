/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:34:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/10 19:20:04 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_SCHEMA_H
# define GAME_SCHEMA_H

# include "config.h"
# include "mge.h"
# include "map.h"

typedef struct s_map t_map;

typedef struct s_game_schema
{
	t_schema	schema;
	t_map		map;
}	t_game_schema;

int	load_game_schema(t_game_schema *gs, void *mlx_ptr);
int	destroy_game_schema(t_game_schema **gs_r);
t_game_schema	*init_game_schema();

#endif