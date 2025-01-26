/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:10:09 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/26 10:27:04 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "sprites.h"
# include "object.h"
# include "schema.h"

typedef struct s_camera
{
	t_object	obj;
	int			width;
	int			height;
	void		*schema;
}	t_camera;

void	update_camera(t_camera	*camera);
void	load_camera(t_camera *camera, void *schema);

#endif
