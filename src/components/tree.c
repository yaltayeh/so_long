/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:24:14 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/16 09:20:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

void animate_tree(t_tree *tree)
{
	tree->clip = (t_clip){56 * tree->status, 0, 56, 94, 1};
}

t_tree	*init_tree(t_game_schema *gs)
{
	t_tree	*tree;
	
	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	load_sprites((void *)tree);
	ft_strlcpy((char *)tree, "tree", NAME_SIZE);
	tree->spr.image = schema_get_image_by_name(gs, "tree");
	tree->clip = (t_clip){0, 0, 56, 94, 1};
	tree->spr.obj.center_point = (t_point){tree->clip.width / 2, 84};
	tree->spr.clips = &tree->clip;
	tree->spr.nb_clip = 1;
	tree->status = 0;
	tree->spr.delay = TREE_DELEY;
	tree->spr.animate = animate_tree;
	tree->spr.obj.destroy = defult_destroy_object;
	return (tree);
}