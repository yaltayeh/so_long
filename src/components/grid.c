/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:47:03 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 11:01:14 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components.h"

int render_grid(t_grid *grid, t_image *frame)
{
	int	y;
	int	x;

	y = grid->offset.y;
	while (y < frame->height)
	{
		x = grid->offset.y;
		while (x < frame->height)
		{
			x += grid->block_w;
		}
		y += grid->block_h;
	}
	
}

int	load_grid(t_grid *grid)
{
	if (load_object(grid, NULL) != 0)
		return (-1);
	return (0);
}