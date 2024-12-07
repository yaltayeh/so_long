/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:24:14 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 08:36:24 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

int	load_tree(t_tree *tree, t_components *components)
{
	load_sprites((void *)tree, NULL, NULL);
	tree->image = components->images[TREE];
	tree->delay = TREE_DELEY;
	return (0);
}