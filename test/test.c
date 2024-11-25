/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:42:43 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/25 22:22:13 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void *ft_malloc(size_t size);
int	ft_open(const char *name);

int main()
{
	char *name;

	name = ft_malloc(32);
	if (!name)
		return (1);
	ft_strlcpy(name, "test/test.txt", -1);
	int fd = ft_open(name);
	ft_fprintf(fd, "test %d\n", fd);
}