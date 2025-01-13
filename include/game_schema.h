/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:34:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 07:31:50 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_SCHEMA_H
# define GAME_SCHEMA_H

# include "sprites.h"
# include "object.h"
# include "schema.h"
# include "config.h"
# include "map.h"
# include "camera.h"

typedef struct s_map	t_map;
typedef struct s_camera	t_camera;

typedef struct s_game_schema
{
	t_schema	schema;
	t_map		map;
	t_camera	camera;
}	t_game_schema;

typedef struct s_image_info
{
	char	*path;
	char 	*name;
}	t_image_info;


int				load_game_schema(t_game_schema *gs, void *mlx_ptr);
int				destroy_game_schema(t_game_schema **gs_r);
t_game_schema	*init_game_schema(void);

#endif