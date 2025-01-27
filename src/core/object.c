/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:58:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/27 07:24:40 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	load_object(void *obj)
{
	ft_bzero(obj, sizeof(t_object));
	ft_strlcpy((char *)obj, "object", NAME_SIZE);
}

void	render_object(void *_obj, t_image *frame, int layer)
{
	t_object	*obj;
	int			(*render)(void *, t_image *, int);

	obj = (t_object *)_obj;
	if (obj->childrens)
		render_object(obj->childrens, frame, layer);
	if (obj->next)
		render_object(obj->next, frame, layer);
	render = obj->render;
	if (render)
		render(obj, frame, layer);
}

void	update_object(void *_obj)
{
	t_object	*obj;
	void		(*update)(void *);	

	obj = (t_object *)_obj;
	update = obj->update;
	if (update)
		update(obj);
	obj->absolute_location = (t_point){0, 0};
	if (obj->parent_location)
		obj->absolute_location = *obj->parent_location;
	obj->absolute_location.x += obj->relative_location.x - obj->center_point.x;
	obj->absolute_location.y += obj->relative_location.y - obj->center_point.y;
	if (obj->childrens)
		update_object(obj->childrens);
	if (obj->next)
		update_object(obj->next);
}

void	defult_destroy_object(void **_obj)
{
	free(*_obj);
	*_obj = NULL;
}

t_object	*get_children_by_name(void *_parent, const char *name)
{
	t_object	*parent;
	t_object	*current;

	parent = (t_object *)_parent;
	current = parent->childrens;
	while (current)
	{
		if (ft_strncmp((char *)current, name, NAME_SIZE) == 0)
			break;
		current = current->next;
	}
	return (current);
}

t_object	*get_children_by_loacation(void *_parent, t_point location)
{
	t_object	*parent;
	t_object	*current;

	parent = (t_object *)_parent;
	current = parent->childrens;
	while (current)
	{
		if (ft_memcmp(&current->relative_location, \
						&location, sizeof(location)) == 0)
			break;
		current = current->next;
	}
	return (current);
}

void	add_children(void *_parent, void *_child)
{
	t_object	*parent;
	t_object	*child;

	parent = (t_object *)_parent;
	child = (t_object *)_child;
	child->next = parent->childrens;
	parent->childrens = child;
}

void	destroy_object(void **_obj)
{
	t_object	*obj;
	void		(*destroy)(void **);

	obj = (t_object *)*_obj;
	ft_fprintf(2, "destroy %s (%d, %d)\n", \
				(char *)obj, \
				obj->relative_location.x, \
				obj->relative_location.y);
	destroy = obj->destroy;
	if (obj->next)
		destroy_object(&obj->next);
	if (destroy)
		destroy(_obj);
}
