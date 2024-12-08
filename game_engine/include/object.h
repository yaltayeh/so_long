/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:05:54 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/08 17:21:42 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "utils.h"

# define NAME_SIZE 16

typedef struct s_object
{
	char	name[NAME_SIZE];
	t_point	location;
	t_point	center_point;
	t_point	*parent_location;
	int		(*render)();
}	t_object;

int	load_object(t_object *obj);

#endif