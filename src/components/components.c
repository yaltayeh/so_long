/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:26:52 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 11:42:13 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"
#include "map.h"

static int	load_component(t_components *components, int i, char type, t_point loc)
{
	t_object	**component_p;

	component_p = components->components + i;
	if (type == 'E')
	{
		*component_p = malloc(sizeof(t_boat));
		if (!*component_p)
			return (-1);
		load_boat((void *)*component_p, components);
	}
	else if (type == 'C')
	{
		*component_p = malloc(sizeof(t_tree));
		if (!*component_p)
			return (-1);
		load_tree((void *)*component_p, components);
	}
	else if (type == 'F')
	{
		*component_p = malloc(sizeof(t_fire));
		if (!*component_p)
			return (-1);
		load_fire((void *)*component_p, components);
	}
	else if (type == 'P')
	{
		*component_p = malloc(sizeof(t_player));
		load_player((void *)*component_p, components);
		components->player = (t_player *)*component_p;
	}
	else
	{
		*component_p = NULL;
		return (-1);
	}
	(*component_p)->location = (t_point){(loc.x + 1) * 2 * TILED_SIZE, (loc.y + 1) * 2 * TILED_SIZE};
	return (0);
}

static int	load_game_schema(t_schema *com, t_map_data *o_map)
{
	int		r;
	int		c;
	int		i;

	r = -1;
	com->nb_components = 0;
	while (++r < o_map->rows)
	{
		c = -1;
		while (++c < o_map->cols)
			if (ft_strchr(COMPONENTS_CHARACTERS, o_map->blocks[r][c]))
				com->nb_components++;
	}
	com->components = ft_calloc(com->nb_components + 1, sizeof(t_object *));
	if (!com->components)
		return (-1);

	i = 0;
	r = -1;
	while (++r < o_map->rows)
	{
		c = -1;
		while (++c < o_map->cols)
			if (ft_strchr(COMPONENTS_CHARACTERS, o_map->blocks[r][c]))
				if (load_component(com, i++, o_map->blocks[r][c], (t_point){c, r}) != 0)
					return (-1);
	}
	return (0);
}

int	load_components(t_components *components, void *mlx_ptr, t_map_data *o_map)
{
	if (open_xpm_file(&components->images[FIRE], mlx_ptr, FIRE_PATH) != 0)
		return (-1);
	if (open_xpm_file(&components->images[TREE], mlx_ptr, TREE_PATH) != 0)
		return (-1);
	if (open_xpm_file(&components->images[BOAT], mlx_ptr, BOAT_PATH) != 0)
		return (-1);
	if (open_xpm_file(&components->images[PLAYER], mlx_ptr, PLAYER_PATH) != 0)
		return (-1);
	if (load_game_schema(components, o_map) != 0)
		return (-1);
	components->spr.obj.render = render_components;
	return (0);
}