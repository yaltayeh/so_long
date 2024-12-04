/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:41:25 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/04 07:45:42 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

static int	check_rectangular_surrounded(t_game *ctx)
{
	char	**map;
	int	r;
	int	i;

	map = ctx->map.map;
	ctx->map.cols = -1;
	r = 0;
	while (map[r])
	{
		if (ctx->map.cols == -1)
			ctx->map.cols = ft_strlen(map[r]);
		if (ctx->map.cols != ft_strlen(map[r]))
				return (MAP_RECTANGULAR);
		if (r == 0 || !map[r + 1])
		{
			i = 0;
			while (map[r][i] == '1')
				i++;
			if (map[r][i] != '\0')
			{
				ft_fprintf(2, "'%s'\n", map[r]);
				return (MAP_SURROUNDED);
			}
		}
		else
			if (map[r][0] != '1' || map[r][ctx->map.cols - 1] != '1')
				return (MAP_SURROUNDED);
		r++;
	}
	ctx->map.rows = r;
	return (0);
}

static int	valid_characters(t_game *ctx)
{
	char	**map;
	int 	r;
	int 	i;

	map = ctx->map.map;
	r = 0;
	while (r < ctx->map.rows)
	{
		i = 0;
		while (map[r][i])
		{
			if (!ft_strchr("01CEP", map[r][i]))
				return (CHARACTER);
			i++;
		}
		r++;
	}
	return (SUCCESS);
}

static int	map_checker(t_game *ctx)
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

// int flood_fill(t_mlx_data *ctx, int x, int y)
// {
	
// 	return (0);
// }

// int	path_check(t_mlx_data *ctx)
// {
// 	int	**map;

// 	if (!ctx->map.map_2d)
// 		return (-1);
	
// 	return (0);
// }






char	**convert_list_to_2d_map(t_stack *map)
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
		map_2d[i] = cur->data.ptr;
		cur = cur->next;
		i++;
	}
	return (map_2d);
}

static void	remove_new_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	line[i] = '\0';
}

static char	**read_map_file(int fd)
{
	t_stack	*map_stack;
	t_node	*node;
	char	*line;
	char	**map;

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
			free(line);
			ft_stack_clear(&map_stack);
			return (NULL);
		}
		ft_stack_tail_push(map_stack, node);
		line = get_next_line(fd);
	}
	map = convert_list_to_2d_map(map_stack);
	map_stack->del_fn.ptr = NULL;
	ft_stack_clear(&map_stack);
	return (map);
}

int	map_parser(const char *map_path, t_game *ctx)
{
	int	fd;

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