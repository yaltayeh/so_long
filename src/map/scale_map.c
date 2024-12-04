/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:23:16 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/04 12:18:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		scale_map(t_map *dst, t_map *src)
{
	int		r;
	int		c;
	char	val;

	dst->rows = src->rows * 2;
	dst->cols = src->cols * 2;
	dst->map = ft_calloc(dst->rows, sizeof(char *));
	if (!dst->map)
		return (-1);
	r = 0;
	while (r < dst->rows)
	{
		dst->map[r] = malloc(dst->cols);
		if (!dst->map[r])
			return (-1);
		c = 0;
		while (c < dst->cols)
		{
			val = src->map[r / 2][c / 2];
			if (val == '1')
				dst->map[r][c] = val;
			else
				dst->map[r][c] = '0';

			c++;
		}
		r++;
	}
	return (0);
}