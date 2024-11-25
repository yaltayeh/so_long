/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:42:43 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/25 20:44:50 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void *ft_malloc(size_t size);

int main()
{
	char *name;

	name = ft_malloc(16);
	if (!name)
		return (1);
	ft_strlcpy(name, "Yacoub", -1);
	ft_printf("name: %s\n", name);
}