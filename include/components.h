/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:27:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 13:29:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPONENTS_H
# define COMPONENTS_H

# include "sprites.h"
# include "schema.h"
# include "config.h"

struct s_map_data;

typedef struct s_fire
{
	t_sprites	spr;
	t_clip		clips[2];
}	t_fire;

typedef struct components
{
	t_sprites	spr;
	t_clip		clip;
}	t_tree;

typedef struct s_boat
{
	t_sprites	spr;
	t_clip		clip;
	enum e_boat_direction
	{
		HORIZONTAL,
		DIAGONAL,
		VERTICAL,
	}	direction;
}	t_boat;

typedef struct s_player
{
	t_sprites			spr;
	t_point				loc;
	t_clip				clip;
	int					logs_count;
	enum e_move_type
	{
		SPELLCAST,
		THRUST,
		WALK,
		SLASH_128
	}	movement;
	enum e_directions
	{
		BACK,
		LEFT,
		FRONT,
		RIGHT
	}	direction;
	int					is_walk;
	int					speed;
}	t_player;

int	load_tree(t_tree *tree, t_schema *schema);
int	load_boat(t_boat *boat, t_schema *schema);
int	load_fire(t_fire *fire, t_schema *schema);
int	load_player(t_player *player, t_schema *schema);

#endif