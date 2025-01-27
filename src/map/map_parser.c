/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:41:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/27 08:23:31 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <stdio.h>

int		check_path(t_grid *p_grid, t_grid *o_grid);
int		valid_characters(t_grid *grid, int *nb);
void	test_flood_fill(t_grid *p_grid, int *nb, int r, int c);
int		check_rectangular_surrounded(t_grid *o_grid);

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
