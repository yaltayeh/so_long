/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:27:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 07:38:24 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPONENTS_H
# define COMPONENTS_H

# include "config.h"
# include "sprites.h"
# include "object.h"
# include "schema.h"

typedef struct s_grid		t_grid;
typedef struct s_game_schema	t_game_schema;

typedef struct s_fire
{
	t_sprites	spr;
	t_clip		clips[2];
}	t_fire;

typedef struct t_tree
{
	t_sprites	spr;
	int			status;
	t_clip		clip;
	int			health;
}	t_tree;

enum e_boat_directions
{
	HORIZONTAL,
	DIAGONAL,
	VERTICAL,
};

typedef struct s_boat
{
	t_sprites				spr;
	t_clip					clip;
	enum e_boat_directions	direction;
}	t_boat;

enum e_directions
{
	BACK,
	LEFT,
	FRONT,
	RIGHT
};

enum e_move_type
{
	SPELLCAST,
	THRUST,
	WALK,
	SLASH_128
};

typedef struct s_player
{
	t_sprites			spr;
	t_point				loc;
	t_clip				clip;
	int					logs_count;
	enum e_move_type	movement;
	enum e_directions	direction;
	int					is_walk;
	int					speed;
	t_game_schema		*gs;
	t_object			*touch_component;
}	t_player;

t_tree		*init_tree(t_game_schema *gs, int i);
t_boat		*init_boat(t_game_schema *gs);
t_fire		*init_fire(t_game_schema *gs);
t_player	*init_player(t_game_schema *gs);
int			load_components(t_game_schema *gs, t_schema *schema, t_grid *o_map);
void		sort_objects(t_object **objects, int nb_object);
int 			damage_tree(t_tree *tree, int damage);

#endif