/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbeg_collecter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:33:53 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/25 20:53:34 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_stack.h>



void *ft_malloc(size_t size);
//static void	ft_free_all() __attribute__((destructor));

static void	ft_free_all()
{
	ft_malloc(-1);
	ft_printf("Free all.\n");
}

void *ft_malloc(size_t size)
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
	{
		ft_stack_clear(&table);
		return (NULL);
	}
	node = ft_init_node((t_data)ret);
	if (!node)
	{
		ft_stack_clear(&table);
		return (NULL);
	}
	ft_stack_tail_push(table, node);
	return (ret);
}