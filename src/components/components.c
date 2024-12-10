/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:26:52 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/10 07:31:48 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"
#include "map.h"
#include "game_schema.h"

static int	load_component(t_schema *schema, int i, char type, t_point loc)
{
	t_object	**component_p;
	int			(*load_func)(void *, t_schema *);

	component_p = schema->components + i;
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
	if (load_func(*component_p, schema) != 0)
		return (-1);
	(*component_p)->location = (t_point){(loc.x + 1) * 2 * TILED_SIZE, (loc.y + 1) * 2 * TILED_SIZE};
	return (0);
}

int	load_components(t_schema *schema, t_map_data *o_map)
{
	int			r;
	int			c;
	int			i;

	schema->nb_components = 0;
	r = -1;
	while (++r < o_map->rows)
	{
		c = -1;
		while (++c < o_map->cols)
			if (ft_strchr(COMPONENTS_CHARACTERS, o_map->blocks[r][c]))
				schema->nb_components++;
	}
	schema->components = ft_calloc(schema->nb_components, sizeof(t_object *));
	if (!schema->components)
		return (-1);
	i = 0;
	r = -1;
	while (++r < o_map->rows)
	{
		c = -1;
		while (++c < o_map->cols)
			if (ft_strchr(COMPONENTS_CHARACTERS, o_map->blocks[r][c]))
				if (load_component(schema, i++, o_map->blocks[r][c], (t_point){c, r}) != 0)
					return (-1);
	}

	return (0);
}

