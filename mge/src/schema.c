/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schema.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:51:32 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/10 08:07:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schema.h"

int	render_schema(void *schema, t_image *frame)
{
	int	i;
	int	(*render)(void *, t_image *);
	t_schema	*_schema;

	_schema = (t_schema *)schema;
	render = _schema->render_schema;
	if (render && render(_schema, frame) != 0)
		return (-1);
	i = 0;
	while (i < _schema->nb_components)
	{
		render = _schema->components[i]->render;
		if (render && render(_schema->components[i], frame) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int load_schema(void *schema, void *data)
{
	int	(*load_schema_ptr)(t_schema *, void *);
	t_schema	*_schema;

	_schema = (t_schema *)schema;
    if (!schema)
		return (-1);
	if (_schema->load_schema)
	{
		load_schema_ptr = _schema->load_schema;
		if (load_schema_ptr)
			return(load_schema_ptr(schema, data));
		return (-1);
	}
    return (0);
}

int	check_schema(void *schema, void *data)
{
	int	(*check_schema_ptr)(void *, void *);
	t_schema	*_schema;

	_schema = (t_schema *)schema;
    if (!schema)
		return (-1);
	check_schema_ptr = _schema->check_schema;
	if (check_schema_ptr)
		return(check_schema_ptr(schema, data));
    return (0);
}

t_object    *schema_get_component_by_name(void *schema, const char *name)
{
	int		i;
	t_schema	*_schema;

	i = 0;
	_schema = (t_schema *)schema;
	while (i < _schema->nb_components)
	{
		if (ft_strncmp((char *)_schema->components[i], \
							name, NAME_SIZE) == 0)
			return (_schema->components[i]);
		i++;
	}
	return (NULL);
}

t_image		*schema_get_image_by_name(void *schema, const char *name)
{
	int		i;
	t_schema	*_schema;

	_schema = (t_schema *)schema;
	i = 0;
	while (i < _schema->resources.nb_images)
	{
		if (ft_strncmp((char *)&_schema->resources.images[i], \
							name, NAME_SIZE) == 0)
			return (&_schema->resources.images[i]);
		i++;
	}
	return (NULL);
}
