/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:23:16 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 20:36:44 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	copy_grid(t_grid *dst, t_grid *src)
{
	int	r;

	dst->rows = src->rows;
	dst->cols = src->cols;
	dst->blocks = ft_calloc(dst->rows, sizeof(char *));
	if (!dst->blocks)
		return (-1);
	r = 0;
	while (r < dst->rows)
	{
		dst->blocks[r] = ft_strdup(src->blocks[r]);
		if (!dst->blocks[r])
			return (-1);
		r++;
	}
	return (0);
}


int	free_grid(t_grid *grid)
{
	int		i;

	i = 0;
	if (grid->blocks)
	{
		while (i < grid->rows && grid->blocks[i])
		{
			free(grid->blocks[i]);
			grid->blocks[i] = NULL;
			i++;
		}
		free(grid->blocks);
		grid->blocks = NULL;
	}
	grid->rows = 0;
	grid->cols = 0;
	return (-1);
}

int	scale_x2_grid(t_grid *dst, t_grid *src)
{
	int		r;
	int		c;

	dst->rows = src->rows * 2;
	dst->cols = src->cols * 2;
	dst->blocks = ft_calloc(dst->rows, sizeof(char *));
	if (!dst->blocks)
		return (-1);
	r = -1;
	while (++r < dst->rows)
	{
		dst->blocks[r] = malloc(dst->cols);
		if (!dst->blocks[r])
			return (-1);
		c = -1;
		while (++c < dst->cols)
		{
			if (src->blocks[r / 2][c / 2] == '1' \
				|| src->blocks[r / 2][c / 2] == 'E')
				dst->blocks[r][c] = '1';
			else
				dst->blocks[r][c] = '0';
		}
	}
	return (0);
}

int	scale_grid(t_grid *o_map, int r, int c)
{
	t_grid	new_map;

	if (o_map->cols >= c && o_map->rows >= r)
		return (0);
	new_map.cols = o_map->cols;
	if (o_map->cols < c)
		new_map.cols = o_map->cols + ((c - o_map->cols + 1) / 2) * 2;
	new_map.rows = o_map->rows;
	if (o_map->rows < r)
		new_map.rows = o_map->rows + ((r - o_map->rows + 1) / 2) * 2;
	new_map.blocks = ft_calloc(r + 1, sizeof(char *));
	if (!new_map.blocks)
		return (-1);
	r = 0;
	while (r < new_map.rows)
	{
		new_map.blocks[r] = ft_calloc(new_map.cols + 1, sizeof(char));
		if (!new_map.blocks[r])
			return (free_grid(&new_map));
		ft_memset(new_map.blocks[r], '1', new_map.cols);
		if ((new_map.rows - o_map->rows) / 2 <= r \
			&& r < (o_map->rows + (new_map.rows - o_map->rows) / 2))
		{
			ft_memcpy(new_map.blocks[r] + (new_map.cols - o_map->cols) / 2, \
				o_map->blocks[r - (new_map.rows - o_map->rows) / 2], \
				o_map->cols);
		}
		r++;
	}
	free_grid(o_map);
	ft_memcpy(o_map, &new_map, sizeof(t_grid));
	return (0);
}

int	get_player_location(t_grid *p_grid, int *r, int *c)
{
	*r = 0;
	while (*r < p_grid->rows)
	{
		*c = 0;
		while (*c < p_grid->cols)
		{
			if (p_grid->blocks[*r][*c] == 'P')
				return (0);
			++*c;
		}
		++*r;
	}
	return (-1);
}
