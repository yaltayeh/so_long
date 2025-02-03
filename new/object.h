/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:39:11 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/03 11:34:07 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

#include "utils.h"

typedef struct s_object
{
	char	name[NAME_SIZE];
	t_point	draw_location;
	t_point	absolute_location;
	t_point	reletive_location;
	t_point	center_point;
	t_point	*parent_location;
}	t_object;

#define OBJECT_OPTIONS(__obj) \
	{"name",	OFFSET(__obj.name), 				OPT_TYPE_STRING,	{.str = ""}},	\
	{"x",		OFFSET(__obj.reletive_location.x),	OPT_TYPE_INT, 		{.i64 = 0}},	\
	{"y",		OFFSET(__obj.reletive_location.y),	OPT_TYPE_INT, 		{.i64 = 0}}	\

#endif