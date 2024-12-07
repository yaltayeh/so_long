/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:27:31 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/30 14:06:22 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

#define BUFFER_SIZE 4096

static int		ft_strexpansion(char **str, size_t added_size)
{
	size_t	total_size;
	char	*new_str;

	if (!*str)
	{
		*str = malloc(sizeof(char));
		if (!*str)
			return (-1);
		**str = '\0';
	}
	if (added_size == 0)
		return (ft_strlen(*str));
	total_size = ft_strlen(*str) + added_size + 1;
	new_str = malloc(total_size);
	if (!new_str)
		return (-1);
	ft_strlcpy(new_str, *str, total_size);
	free(*str);
	*str = new_str;
	return (total_size);
}

char	*read_file(int fd)
{
	char	*content;
	ssize_t	bytes_read;
	size_t	total_bytes;

	bytes_read = 0;
	total_bytes = 0;
	content = NULL;
	while (!content || bytes_read > 0)
	{
		if (ft_strexpansion(&content, BUFFER_SIZE) == -1)
			return (NULL);
		bytes_read = read(fd, content + bytes_read, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(content);
			return (NULL);
		}
		total_bytes += bytes_read;
		content[total_bytes] = '\0';
	}
	return (content);
}