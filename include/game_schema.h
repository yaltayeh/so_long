/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:34:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 10:18:40 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_SCHEMA_H
# define GAME_SCHEMA_H

# include "object.h"
# include "schema.h"
# include "map.h"
# include "camera.h"
# include "components.h"


/*
Clips
	0:		banner up
	1:		icon
	2-6:	digits
	7:		banner down
	8: 		icon
	9-13:	digits
*/
typedef struct s_banner
{
	t_object	spr;
	t_image		*image;
	t_clip		clips[14];
	int			nb_collect;
	int			*logs_collected;
	int			*movement;
}	t_banner;

typedef struct s_image_info
{
	char	*path;
	char	*name;
}	t_image_info;

typedef struct s_game_schema
{
	t_schema	schema;
	t_object	components;
	t_map		map;
	t_camera	camera;
	t_banner	banner;
}	t_game_schema;

t_game_schema	*init_game_schema(void);

#endif