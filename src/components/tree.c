/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:24:14 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 20:17:29 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

int update_tree(t_tree *tree)
{
	tree->clip = (t_clip){56 * 0, 0, 56, 94};
	return (0);
}

int	load_tree(t_tree *tree, t_schema *schema)
{
	load_sprites((void *)tree);
	ft_strlcpy((char *)tree, "tree", NAME_SIZE);
	tree->spr.obj.center_point = (t_point){132, 28};
	tree->spr.image = get_image_by_name(schema, "tree");
	tree->clip = (t_clip){0, 0, 56, 94};
	tree->spr.clips = &tree->clip;
	tree->spr.nb_clip = 1;
	tree->spr.delay = TREE_DELEY;
	tree->spr.update = update_tree;
	return (0);
}