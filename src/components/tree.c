/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:24:14 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/25 00:39:56 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

void	animate_tree(t_tree *tree)
{
	tree->clip = (t_clip){56 * tree->status, 0, 56, 94, 1};
}

int	damage_tree(t_tree *tree, int damage)
{
	if (tree->status != 2)
	{
		tree->health -= damage;
		if (tree->health <= 0)
		{
			tree->status = 2;
			return (1);
		}
	}
	return (0);
}

t_tree	*init_tree(t_game_schema *gs, int i)
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
	tree->status = i & 1;
	tree->spr.delay = TREE_DELEY;
	tree->spr.animate = animate_tree;
	tree->spr.obj.destroy = defult_destroy_object;
	
	tree->health = 120 - 20 * (i & 1);
	load_health_bar(gs, &tree->health_bar, tree, &tree->health, HB_DARK_RED_1);
	((t_object *)tree)->next = &tree->health_bar;
	return (tree);
}
