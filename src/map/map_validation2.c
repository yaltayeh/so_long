/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:49:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/29 08:56:55 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	get_player_location(t_grid *p_grid, int *r, int *c);

void	test_flood_fill(t_grid *p_grid, int *nb, int r, int c)
{
	if (r < 0 || r >= p_grid->rows || c < 0 \
		|| c >= p_grid->cols || p_grid->blocks[r][c] == '1')
		return ;
	if (p_grid->blocks[r][c] == 'P')
		--nb[0];
	if (p_grid->blocks[r][c] == 'E')
		--nb[1];
	if (p_grid->blocks[r][c] == 'C')
		--nb[2];
	if (p_grid->blocks[r][c] == 'C' || p_grid->blocks[r][c] == 'P' \
		|| p_grid->blocks[r][c] == 'F')
		p_grid->blocks[r][c] += 32;
	else if (p_grid->blocks[r][c] == '0')
		p_grid->blocks[r][c] = ' ';
	else if (p_grid->blocks[r][c] == 'E')
	{
		p_grid->blocks[r][c] = 'e';
		return ;
	}
	else
		return ;
	test_flood_fill(p_grid, nb, r - 1, c);
	test_flood_fill(p_grid, nb, r + 1, c);
	test_flood_fill(p_grid, nb, r, c + 1);
	test_flood_fill(p_grid, nb, r, c - 1);
}

int	valid_characters(t_grid *grid, int *nb)
{
	int	r;
	int	c;

	r = 0;
	while (r < grid->rows)
	{
		c = 0;
		while (c < grid->cols)
		{
			if (!ft_strchr("01PECF", grid->blocks[r][c]))
			{
				print_error_line(grid->blocks, r, c, "character not valid");
				return (-1);
			}
			if (grid->blocks[r][c] == 'P')
				++nb[0];
			if (grid->blocks[r][c] == 'E')
				++nb[1];
			if (grid->blocks[r][c] == 'C')
				++nb[2];
			c++;
		}
		r++;
	}
	return (0);
}

int	check_path(t_grid *p_grid, t_grid *o_grid)
{
	int		r;
	int		c;
	int		nb[3];
	int		nb_collect;

	ft_bzero(nb, sizeof(nb));
	if (valid_characters(p_grid, nb) != 0)
		return (-1);
	if (nb[0] != 1 || nb[1] != 1 || nb[2] < 1)
		return (print_error_number1(p_grid, nb));
	nb_collect = nb[2];
	if (get_player_location(p_grid, &r, &c) != 0)
		return (-1);
	test_flood_fill(p_grid, nb, r, c);
	if (nb[1] != 0 || nb[2] != 0)
		return (print_error_number2(p_grid, o_grid, nb));
	return (nb_collect);
}
