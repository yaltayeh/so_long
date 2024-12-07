/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:05:54 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/05 18:13:05 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "utils.h"

typedef struct s_object
{
	t_point	loc;
	int		(*render)();
	void	*mlx_ptr;
}	t_object;

int	load_object(t_object *obj, void *mlx_ptr);

#endif