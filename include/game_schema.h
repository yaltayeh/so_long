/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:34:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/27 17:20:40 by yaltayeh         ###   ########.fr       */
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
# include "components.h"

typedef struct s_map	t_map;
typedef struct s_camera	t_camera;


typedef struct s_banner
{
	t_object	obj;
	int	nb_collect;
	int	logs_collected;
}	t_banner;

typedef struct s_image_info
{
	char	*path;
	char 	*name;
}	t_image_info;


typedef struct s_game_schema
{
	t_schema	schema;
	t_object	components;
	t_map		map;
	t_camera	camera;
	t_banner	banner;
}	t_game_schema;

t_game_schema	*init_game_schema();

#endif