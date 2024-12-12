/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:49:11 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/11 13:59:38 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	update_camera(t_camera	*camera)
{
	t_object	*player;
	
	player = schema_get_component_by_name(camera->schema, "player");
	if (player)
	{
		camera->frame.x = -player->relative_location.x + 500;
		camera->frame.y = -player->relative_location.y + 325;
	}
}