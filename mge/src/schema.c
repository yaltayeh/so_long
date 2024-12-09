/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schema.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:51:32 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 12:00:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schema.h"

int	render_schema(t_schema *schema, t_image *frame)
{
	int	i;
	int	(*render)(void *, t_image *);

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

int load_schema(t_schema *schema, void *data)
{
	int	(*load_schema_ptr)(t_schema *, void *);

    if (!schema)
		return (-1);
	if (schema->load_schema)
	{
		load_schema_ptr = schema->load_schema;
		if (load_schema_ptr)
			return(load_schema_ptr(schema, data));
		return (-1);
	}
    return (0);
}


t_object    *get_component_by_name(t_schema *schema, const char *name)
{
	int		i;

	i = 0;
	while (i < schema->nb_components)
	{
		if (ft_strncmp((char *)&schema->components[i], \
							name, NAME_SIZE) == 0)
			return (schema->components[i]);
		i++;
	}
	return (NULL);
}

t_image		*get_image_by_name(t_schema *schema, const char *name)
{
	int		i;

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