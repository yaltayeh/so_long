/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:23:16 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 07:52:46 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	scale_grid(t_grid *dst, t_grid *src)
{
	int		r;
	int		c;
	char	val;

	dst->rows = src->rows * 2;
	dst->cols = src->cols * 2;
	dst->blocks = ft_calloc(dst->rows, sizeof(char *));
	if (!dst->blocks)
		return (-1);
	r = 0;
	while (r < dst->rows)
	{
		dst->blocks[r] = malloc(dst->cols);
		if (!dst->blocks[r])
			return (-1);
		c = 0;
		while (c < dst->cols)
		{
			val = src->blocks[r / 2][c / 2];
			if (val == '1' || val == 'E')
				dst->blocks[r][c] = '1';
			else
				dst->blocks[r][c] = '0';
			c++;
		}
		r++;
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
