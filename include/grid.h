/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:01:54 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/02 11:46:45 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_H
# define GRID_H

# include "utils.h"

typedef struct s_grid
{
	char	**blocks;
	int		rows;
	int		cols;
}	t_grid;

int		scale_x2_grid(t_grid *dst, t_grid *src);
int		copy_grid(t_grid *dst, t_grid *src);
int		free_grid(t_grid *grid);
int		map_normalization(t_grid *o_map, int rows, int cols);

#endif