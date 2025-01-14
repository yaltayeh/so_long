/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:58:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/13 17:28:43 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

int	load_object(void *_obj)
{
	t_object	*obj;

	obj = (t_object *)_obj;
	ft_strlcpy((char *)obj, "object", NAME_SIZE);
	obj->absolute_location = (t_point){0, 0};
	obj->relative_location = (t_point){0, 0};
	obj->center_point = (t_point){0, 0};
	obj->parent_location = NULL;
	obj->update = NULL;
	obj->render = NULL;
	obj->destroy = NULL;
	return (0);
}

int	render_object(void *_obj, t_image *frame, int layer)
{
	t_object	*obj;
	int			(*render)(void *, t_image *, int);

	obj = (t_object *)_obj;
	render = obj->render;
	if (render)
		return (render(obj, frame, layer));
	return (0);
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
}

void	defult_destroy_object(void **_obj)
{
	free(*_obj);
	*_obj = NULL;
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
	if (destroy)
		destroy(_obj);
}
