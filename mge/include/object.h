/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:05:54 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/15 12:13:24 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "utils.h"

typedef struct s_object
{
	char		name[NAME_SIZE];
	t_point		absolute_location;
	t_point		relative_location;
	t_point		center_point;
	t_point		*parent_location;
	/*void update_object(t_object *obj)*/
	void		(*update)();
	/*void render_object(t_object *obj, t_image *frame, int layer)*/
	int			(*render)();
	/*void destroy_object(t_object **obj)*/
	void		(*destroy)();
	/*void collision_object(t_object *obj, t_object *tangible)*/
	void		(*collision)();
}	t_object;

int		load_object(void *_obj);
int		render_object(void *obj, t_image *frame, int layer);
void	update_object(void *_obj);
void	destroy_object(void **_obj);
void	defult_destroy_object(void **_obj);

#endif