/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:10:09 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 07:32:45 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "sprites.h"
# include "object.h"
# include "schema.h"

typedef struct s_camera
{
	t_clip	frame;
	void	*schema;
}	t_camera;

void	update_camera(t_camera	*camera);

#endif
