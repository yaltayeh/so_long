/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:47:44 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/27 08:59:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"

int	open_xpm_file(t_image *image, void *mlx_ptr, \
						char *filename, const char *img_name)
{
	ft_strlcpy((char *)image, img_name, NAME_SIZE);
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, filename, \
									&image->width, &image->height);
	if (!image->img_ptr)
		return (-1);
	if (load_image_data(image) != 0)
		return (-1);
	return (0);
}

t_object	*pop_player(t_object *components)
{
	t_object	*current;
	t_object	*prev;

	current = components->childrens;
	prev = NULL;
	while (current)
	{
		if (is_object_type(current, "player"))
		{
			if (!prev && !current->next)
				return (NULL);
			if (!prev)
				components->childrens = current->next;
			else
				prev->next = current->next;
			current->next = NULL;
			return (current);
		}
		prev = current;
		current = current->next;
	}
	return (NULL);
}
