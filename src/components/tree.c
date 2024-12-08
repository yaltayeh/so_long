/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:24:14 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/08 08:40:34 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

int update_tree(t_tree *tree)
{
	tree->clip = (t_clip){56 * 0, 0, 56, 94};
	return (0);
}

int	load_tree(t_tree *tree, t_components *components)
{
	load_sprites((void *)tree, NULL, NULL);
	tree->spr.obj.center_point = (t_point){132, 28};
	tree->spr.image = components->images[TREE];
	tree->clip = (t_clip){0, 0, 56, 94};
	tree->spr.clip = &tree->clip;
	tree->spr.nb_clip = 1;
	tree->spr.delay = TREE_DELEY;
	tree->spr.update = update_tree;
	return (0);
}