/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:41:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/01 09:21:05 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

static int	check_rectangular_surrounded(t_mlx_data *ctx)
{
	t_node	*cur;
	char	*row;
	int		i;
	size_t	col;

	cur = ctx->map->head;
	if (cur)
	{
		row = cur->data.ptr;
		col = ft_strlen(row);
		i = 0;
		while (row[i] == '1')
			i++;
		if (row[i] != '\0')
			return (MAP_SURROUNDED);
	}
	i = 1;
	while (cur)
	{
		row = cur->data.ptr;
		if (col != ft_strlen(row))
			return (MAP_RECTANGULAR);
		if (row[0] != '1' || row[col - 1] != '1')
			return (MAP_SURROUNDED);
		cur = cur->next;
		i++;
	}
	cur = ctx->map->tail;
	if (cur)
	{
		row = cur->data.ptr;
		i = 0;
		while (row[i] == '1')
			i++;
		if (row[i] != '\0')
			return (MAP_SURROUNDED);
	}
	return (0);
}

static int	valid_characters(t_mlx_data *ctx)
{
	t_node	*cur;
	char	*row;
	size_t	i;

	cur = ctx->map->head;
	while (cur)
	{
		row = cur->data.ptr;
		i = 0;
		while (row[i])
		{
			if (!ft_strchr("01CEP", row[i]))
				return (CHARACTER);
			i++;
		}
		cur = cur->next;
	}
	return (SUCCESS);
}

static int	map_checker(t_mlx_data *ctx)
{
	int	err;

	err = check_rectangular_surrounded(ctx);
	if (err != SUCCESS)
		return (err);
	err = valid_characters(ctx);
	if (err != SUCCESS)
		return (err);
	// err = check_closed_surrounded(ctx);
	// if (err != SUCCESS)
	// 	return (err);
	return (SUCCESS);
}

int	**convert_map_to_2d_array(t_stack *map)
{
	char	**map_2d;
	t_node	*cur;
	int		i;

	cur = map->head;
	if (!cur)
		return (NULL);
	map_2d = ft_calloc(ft_stack_size(map) + 1, sizeof(char *));
	if (!map_2d)
		return (NULL);
	i = 0;
	while (cur)
	{
		map_2d[i] = ft_strdup(cur->data.ptr);
		if (!map_2d[i])
		{
			while (i-- > 0)
				free(map_2d[i]);
			free(map_2d);
			return (NULL);
		}
		cur = cur->next;
	}
	return (map_2d);
}

int flood_fill(t_mlx_data *ctx, int x, int y)
{
	
	return (0);
}

int	add_node_to_tail(t_mlx_data *ctx, t_stack *q, int x, int y)
{
	t_node	*node;
	t_pix	*pix;
	char	character;

	character = get_character(ctx, x, y);
	if (character == 255)
		return (SUCCESS);
	pix = malloc(sizeof(t_pix));
	if (!pix)
		return (MALLOC);
	pix->row = y;
	pix->col = x;
	pix->c = character;
	node = ft_init_node((t_data)(void *)pix);
	if (!node)
		return (MALLOC);
	ft_stack_tail_push(q, node);
	return (SUCCESS);
}

int	path_check(t_mlx_data *ctx)
{
	int	**map;

	if (!ctx->map.map_2d)
		return (-1);
	
	return (0);
}




static void	remove_new_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	line[i] = '\0';
}

static int	**read_map_file(int fd)
{
	t_stack	*map_stack;
	t_node	*node;
	char	*line;
	int		**map;

	map_stack = ft_init_stack(FT_POINTER, NULL, NULL, free);
	if (!map_stack)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		remove_new_line(line);
		node = ft_init_node((t_data)(void *)line);
		if (!node)
		{
			ft_stack_clear(&map_stack);
			free(line);
			return (NULL);
		}
		ft_stack_tail_push(map_stack, node);
		line = get_next_line(fd);
	}
	map = convert_map_to_2d_array(map_stack);
	ft_stack_clear(&map_stack);
	return (map);
}

int map_parser(const char *map_path, t_mlx_data *ctx)
{
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		perror(map_path);
		return (-1);
	}
	ctx->map.map = read_map_file(fd);
	close(fd);
	if (!ctx->map.map)
		return (-1);
	
	return (map_checker(ctx));
}