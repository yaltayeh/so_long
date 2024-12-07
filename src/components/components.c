/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:26:52 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 15:34:23 by yaltayeh         ###   ########.fr       */
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
		load_boat((void *)*component_p, components);
	}
	else if (type == 'C')
	{
		*component_p = malloc(sizeof(t_tree));
		load_tree((void *)*component_p, components);
	}
	else if (type == 'F')
	{
		*component_p = malloc(sizeof(t_fire));
		load_fire((void *)*component_p, components);
	}
	else
		*component_p = NULL;
	(*component_p)->loc = (t_point){loc.x * 2 * 64 + 32, loc.y * 2 * 64 + 32};
	return (0);
}

static int	init_components(t_components *com, t_map_data *o_map)
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

static int open_xpm_file(t_image *image, void *mlx_ptr, char *filename)
{
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, filename, &image->width, &image->height);
	if (!image->img_ptr)
		return (-1);
	if (load_image(image) != 0)
		return (-1);
	return (0);
}

static int	render_components(t_components *components, t_image *frame)
{
	int	i;
	int	(*render)(void *, t_image *);

	i = 0;
	while (i < components->nb_components)
	{
		render = components->components[i]->render;
		if (render && render(components->components[i], frame) != 0)
			return (-1);
		i++;
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
	if (init_components(components, o_map) != 0)
		return (-1);
	components->spr.obj.render = render_components;
	return (0);
}