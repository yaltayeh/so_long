/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:24:14 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/13 11:59:50 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

void animate_tree(t_tree *tree)
{
	tree->clip = (t_clip){56 * 0, 0, 56, 94, 1};
}

int	load_tree(t_tree *tree, t_game_schema *gs)
{
	load_sprites((void *)tree);
	ft_strlcpy((char *)tree, "tree", NAME_SIZE);
	tree->spr.image = schema_get_image_by_name(gs, "tree");
	tree->clip = (t_clip){0, 0, 56, 94, 1};
	tree->spr.obj.center_point = (t_point){tree->clip.width / 2, 64};
	tree->spr.clips = &tree->clip;
	tree->spr.nb_clip = 1;
	tree->spr.delay = TREE_DELEY;
	tree->spr.animate = animate_tree;
	return (0);
}