/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:41:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/15 11:54:37 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_rectangular_surrounded(t_grid *o_grid)
{
	int	r;
	int	i;

	o_grid->cols = -1;
	r = 0;
	while (o_grid->blocks[r])
	{
		if (o_grid->cols == -1)
			o_grid->cols = ft_strlen(o_grid->blocks[r]);
		if (o_grid->cols != (int)ft_strlen(o_grid->blocks[r]))
			return (-1);
		if (r == 0 || !o_grid->blocks[r + 1])
		{
			i = 0;
			while (o_grid->blocks[r][i] == '1' || o_grid->blocks[r][i] == 'E')
				i++;
			if (o_grid->blocks[r][i] != '\0')
			{
				print_error_line(o_grid->blocks, r, i, "map not closed");
				return (-1);
			}
		}
		else if (o_grid->blocks[r][0] != '1' \
				|| o_grid->blocks[r][o_grid->cols - 1] != '1')
		{
			i = o_grid->cols - 1;
			if (o_grid->blocks[r][0] != '1')
				i = 0;
			print_error_line(o_grid->blocks, r, i, "map not closed");
			return (-1);
		}
		r++;
	}
	o_grid->rows = r;
	return (0);
}

static void	test_flood_fill(t_grid *p_grid, int *nb, int r, int c)
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

static int	valid_characters(t_grid *grid, int *nb)
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

static int	check_path(t_grid *p_grid, t_grid *o_grid)
{
	int	r;
	int	c;
	int	nb[3];
	int	nb_collect;

	ft_bzero(nb, sizeof(nb));
	if (valid_characters(p_grid, nb) != 0)
		return (-1);
	if (nb[0] != 1 || nb[1] != 1 || nb[2] < 1)
		return (print_error_number1(p_grid, nb));
	r = -1;
	nb_collect = nb[2];
	while (++r < p_grid->rows)
	{
		c = -1;
		while (++c < p_grid->cols)
		{
			if (p_grid->blocks[r][c] == 'P')
			{
				test_flood_fill(p_grid, nb, r, c);
				if (nb[1] != 0 || nb[2] != 0)
					return (print_error_number2(p_grid, o_grid, nb));
				return (nb_collect);
			}
		}
	}
	return (-1);
}

static void	remove_new_line(char *line)
{
	while (*line && *line != '\n')
		line++;
	*line = '\0';
}

static char	**read_map_file(int fd, int i)
{
	char	*line;
	char	**map;

	line = get_next_line(fd);
	if (!line)
		return (ft_calloc(i + 1, sizeof(char *)));
	remove_new_line(line);
	map = read_map_file(fd, i + 1);
	if (map)
		map[i] = line;
	else
		free(line);
	return (map);
}

int	map_parser(t_map *map, const char *map_path)
{
	int	fd;
	int	nb_collect;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		perror(map_path);
		return (-1);
	}
	map->o_grid.blocks = read_map_file(fd, 0);
	close(fd);
	if (!map->o_grid.blocks)
		return (-1);
	if (check_rectangular_surrounded(&map->o_grid) != 0)
		return (-1);
	if (copy_grid(&map->p_grid, &map->o_grid) != 0)
		return (-1);
	nb_collect = check_path(&map->p_grid, &map->o_grid);
	if (nb_collect < 1)
		return (-1);
	if (scale_grid(&map->s_grid, &map->o_grid) != 0)
		return (-1);
	return (nb_collect);
}
