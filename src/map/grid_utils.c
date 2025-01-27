/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:23:16 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/27 08:16:59 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	scale_grid(t_grid *dst, t_grid *src)
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

void	free_grid(t_grid *grid)
{
	int		i;

	i = 0;
	if (grid->blocks)
	{
		while (i < grid->rows && grid->blocks[i])
		{
			free(grid->blocks[i]);
			i++;
		}
		free(grid->blocks);
		grid->blocks = NULL;
	}
}
