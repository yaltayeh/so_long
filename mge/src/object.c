/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:58:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/08 17:23:04 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

int	load_object(t_object *obj)
{
	ft_strlcpy((char *)obj, "object", NAME_SIZE);
	obj->location = (t_point){0, 0};
	obj->center_point = (t_point){0, 0};
	obj->parent_location = NULL;
	obj->render = (void *)0;
	return (0);
}