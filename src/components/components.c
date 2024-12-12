/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:26:52 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/11 20:20:10 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"
#include "map.h"
#include "game_schema.h"

static int	load_component(t_game_schema *gs, int i, char type, t_point loc)
{
	t_object	**component_p;
	int			(*load_func)(void *, void *);

	component_p = gs->schema.components + i;
	*component_p = NULL;
	if (type == 'E')
	{
		*component_p = malloc(sizeof(t_boat));
		load_func = (void *)load_boat;
	}
	else if (type == 'C')
	{
		*component_p = malloc(sizeof(t_tree));
		load_func = (void *)load_tree;
	}
	else if (type == 'F')
	{
		*component_p = malloc(sizeof(t_fire));
		load_func = (void *)load_fire;
	}
	else if (type == 'P')
	{
		*component_p = malloc(sizeof(t_player));
		load_func = (void *)load_player;
	}
	if (!*component_p)
		return (-1);
	if (load_func(*component_p, gs) != 0)
		return (-1);
	(*component_p)->relative_location = (t_point){(loc.x * 2 + 1) * TILED_SIZE, (loc.y * 2 + 1) * TILED_SIZE};
	(*component_p)->parent_location = (void *)&gs->camera.frame;
	return (0);
}

int	load_components(t_game_schema *gs, t_map_data *o_map)
{
	int			r;
	int			c;
	int			i;

	gs->schema.nb_components = 0;
	r = -1;
	while (++r < o_map->rows)
	{
		c = -1;
		while (++c < o_map->cols)
			if (ft_strchr(COMPONENTS_CHARACTERS, o_map->blocks[r][c]))
				gs->schema.nb_components++;
	}
	gs->schema.components = ft_calloc(gs->schema.nb_components, sizeof(t_object *));
	if (!gs->schema.components)
		return (-1);
	i = 0;
	r = -1;
	while (++r < o_map->rows)
	{
		c = -1;
		while (++c < o_map->cols)
			if (ft_strchr(COMPONENTS_CHARACTERS, o_map->blocks[r][c]))
				if (load_component(gs, i++, o_map->blocks[r][c], (t_point){c, r}) != 0)
					return (-1);
	}

	return (0);
}


static int	object_cmp(t_object *obj1, t_object *obj2)
{
	int	a;
	int	b;

	a = obj1->relative_location.y;
	b = obj2->relative_location.y;
	if (a < b)
		return (-1);
	if (a > b)
		return (1);
	return (0);
}

static void	swap_objects(t_object **a, t_object **b)
{
	t_object	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_objects(t_object **objects, int nb_object)
{
	int	i;
	int	j;
	int	test;

	i = 0;
	while (i < nb_object - 1)
	{
		j = i + 1;
		test = -1;
		while (test < 0 && j < nb_object)
		{
			test = object_cmp(objects[i], objects[j]);
			j++;
		}
		if (test > 0)
			swap_objects(objects + i, objects + j - 1);
		i++;
	}
	
}
