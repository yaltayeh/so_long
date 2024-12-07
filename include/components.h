/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:27:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 10:59:36 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPONENTS_H
# define COMPONENTS_H

# include "sprites.h"

struct s_map_data;

enum e_components_id
{
	FIRE,
	TREE,
	BOAT,
};

typedef struct s_components
{
	t_sprites	spr;
	t_image		images[3];
	t_sprites	*components;
	int			nb_components;
}	t_components;

typedef t_sprites	t_fire;
typedef t_sprites	t_tree;

typedef struct s_boat
{
	t_sprites	spr;
	t_clip		clip;
}	t_boat;

typedef	struct s_grid
{
	t_object	obj;
	t_point		offset;
	int			block_w;
	int			block_h;
	int			color;
}	t_grid;

int	load_components(t_components *components, void *mlx_ptr, \
							struct s_map_data *o_map);

int	load_tree(t_tree *tree, t_components *components);
int	load_boat(t_boat *boat, t_components *components);
int	load_fire(t_fire *fire, t_components *components);
int	load_grid(t_grid *grid);

#endif