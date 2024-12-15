/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:10:09 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/15 13:08:05 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "mge.h"

typedef struct s_camera
{
	t_clip	frame;
	void	*schema;
}	t_camera;

void	update_camera(t_camera	*camera);

#endif
