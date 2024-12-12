/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schema.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:51:32 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/12 10:57:20 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schema.h"

void	sort_objects(t_object **objects, int nb_object);

int	render_schema(void *_schema, t_image *frame)
{
	int			i;
	int			(*render)(void *, t_image *);
	int			(*update)(void *);
	t_schema	*schema;

	schema = (t_schema *)_schema;
	i = 0;
	while (i < schema->nb_components)
	{
		update = schema->components[i]->update;
		if (update && update(schema->components[i]) != 0)
			return (-1);
		i++;
	}
	render = schema->render_schema;
	if (render && render(schema, frame) != 0)
		return (-1);
	sort_objects((void *)schema->components, schema->nb_components);
	i = 0;
	while (i < schema->nb_components)
	{
		render = schema->components[i]->render;
		if (render && render(schema->components[i], frame) != 0)
			return (-1);
		i++;
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
