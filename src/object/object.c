/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:58:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/05 18:31:46 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

int	load_object(t_object *obj, void *mlx_ptr)
{
	obj->loc = (t_point){0, 0};
	obj->mlx_ptr = mlx_ptr;
	obj->render = (void *)0;
	return (0);
}