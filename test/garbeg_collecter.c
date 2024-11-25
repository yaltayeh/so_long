/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbeg_collecter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:33:53 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/25 21:13:55 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_stack.h>
#include <fcntl.h>

void *ft_malloc(size_t size);
static void	ft_destroy() __attribute__((destructor));
int	ft_open(const char *name);


static void	ft_destroy()
{
	ft_open((void *)-1);
	ft_malloc(-1);
}

void	*ft_malloc(size_t size)
{
	void			*ret;
	static t_stack	*table;
	t_node			*node;

	if (size == -1)
	{
		ft_stack_clear(&table);
		return (NULL);
	}
	if (!table)
	{
		table = ft_init_stack(FT_POINTER, NULL, NULL, free);
		if (!table)
			return (NULL);
	}
	ret = malloc(size);
	if (!ret)
		return (ft_malloc(-1));
	node = ft_init_node((t_data)ret);
	if (!node)
		return (ft_malloc(-1));
	ft_stack_tail_push(table, node);
	return (ret);
}


int	ft_open(const char *name)
{
	int				fd;
	static t_stack	*table;
	t_node			*node;

	if (name == (void *)-1)
	{
		ft_stack_clear(&table);
		return (-1);
	}
	if (!table)
	{
		table = ft_init_stack(FT_INT, NULL, NULL, close);
		if (!table)
			return (-1);
	}
	fd = open(name, O_WRONLY);
	if (fd == -1)
		return (-1);
	node = ft_init_node((t_data)fd);
	if (!node)
		return (-1);
	ft_stack_tail_push(table, node);
	return (fd);
}