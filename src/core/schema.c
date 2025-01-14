/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schema.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:51:32 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/13 17:35:32 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schema.h"

void	sort_objects(t_object **objects, int nb_object);

int	render_schema(void *_schema, t_image *frame)
{
	int			i;
	int			(*render)(void *, t_image *);
	t_schema	*schema;
	int			layer;

	schema = (t_schema *)_schema;
	render = schema->render_schema;
	if (render && render(schema, frame) != 0)
		return (-1);
	i = -1;
	while (++i < schema->nb_components)
		update_object(schema->components[i]);
	sort_objects((void *)schema->components, schema->nb_components);
	layer = 0;
	while (layer < 3)
	{
		i = -1;
		while (++i < schema->nb_components)
			render_object(schema->components[i], frame, layer);
		layer++;
	}
	return (0);
}

int	load_schema(void *_schema, void *data)
{
	int			(*load_schema_ptr)(t_schema *, void *);
	t_schema	*schema;

	schema = (t_schema *)_schema;
	if (!schema)
		return (-1);
	if (schema->load_schema)
	{
		load_schema_ptr = schema->load_schema;
		if (load_schema_ptr)
			return (load_schema_ptr(schema, data));
		return (-1);
	}
	return (0);
}

int	check_schema(void *_schema, void *data)
{
	int			(*check_schema_ptr)(void *, void *);
	t_schema	*schema;

	schema = (t_schema *)_schema;
	if (!schema)
		return (-1);
	check_schema_ptr = schema->check_schema;
	if (check_schema_ptr)
		return (check_schema_ptr(schema, data));
	return (0);
}

void	destroy_schema(void **_schema)
{
	t_schema	*schema;
	void		(*destroy)(void **);
	int			i;

	schema = (t_schema *)*_schema;
	destroy = (void *)schema->destroy_schema;
	if (schema->components)
	{
		i = -1;
		while (++i < schema->nb_components)
			destroy_object((void **)&schema->components[i]);
		free(schema->components);
		schema->components = NULL;
		schema->nb_components = 0;
	}
	ft_fprintf(2, "destroy objects\n");
	if (schema->resources.images)
	{
		i = -1;
		while (++i < schema->resources.nb_images)
			mlx_destroy_image(schema->mlx_ptr, \
					schema->resources.images[i].img_ptr);
		free(schema->resources.images);
	}
	// ft_bzero(schema + sizeof(schema->mlx_ptr), 
	// 		sizeof(*schema) - sizeof(schema->mlx_ptr));
	if (destroy)
		destroy(_schema);
}

t_object	*schema_get_component_by_name(void *_schema, const char *name)
{
	int			i;
	t_schema	*schema;

	i = 0;
	schema = (t_schema *)_schema;
	while (i < schema->nb_components)
	{
		if (ft_strncmp((char *)schema->components[i], \
							name, NAME_SIZE) == 0)
			return (schema->components[i]);
		i++;
	}
	return (NULL);
}

t_object	*schema_get_component_by_loacation(void *_schema, t_point location)
{
	t_schema	*schema;
	int			i;

	i = 0;
	schema = (t_schema *)_schema;
	while (i < schema->nb_components)
	{
		if (ft_memcmp(&schema->components[i]->relative_location, \
						&location, sizeof(location)) == 0)
			return (schema->components[i]);
		i++;
	}
	return (NULL);
}

t_image	*schema_get_image_by_name(void *_schema, const char *name)
{
	int			i;
	t_schema	*schema;

	schema = (t_schema *)_schema;
	i = 0;
	while (i < schema->resources.nb_images)
	{
		if (ft_strncmp((char *)&schema->resources.images[i], \
							name, NAME_SIZE) == 0)
			return (&schema->resources.images[i]);
		i++;
	}
	return (NULL);
}
