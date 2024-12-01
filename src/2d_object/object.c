/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:57:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/30 22:41:21 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_sprites(t_2d_object *obj, char *sprites_path)
{
	struct s_image *sprites;

	sprites = &obj->sprites;

	sprites->img_ptr = mlx_xpm_file_to_image(obj->mlx_ptr, sprites_path, 
								&sprites->width, &sprites->height);
	if (!sprites->img_ptr)
		return (-1);
	if (load_image(sprites) == -1)
		return (-1);
	return (0);	
}

void *destroy_object(t_2d_object	**obj)
{
	if (*obj)
	{
		if ((*obj)->sprites.img_ptr)
			mlx_destroy_image((*obj)->mlx_ptr, (*obj)->sprites.img_ptr);
		if ((*obj)->object.img_ptr)
			mlx_destroy_image((*obj)->mlx_ptr, (*obj)->object.img_ptr);
		free(*obj);
	}
	*obj = NULL;
	return (NULL);
}


t_2d_object	*init_character(void *mlx_ptr, char *sprites_path)
{
	t_2d_object	*obj;

	obj = ft_calloc(1, sizeof(t_2d_object));
	if (!obj)
		return (NULL);
	obj->mlx_ptr = mlx_ptr;

	if (load_sprites(obj, sprites_path) == -1)
		return (destroy_object(&obj));
	obj->object.width = 64;
	obj->object.height = 64;
	obj->object.img_ptr = mlx_new_image(mlx_ptr, obj->object.width, obj->object.height);
	if (!obj->object.img_ptr)
		return (destroy_object(&obj));
	if (load_image(&obj->object) == -1)
		return (destroy_object(&obj));
	obj->col = obj->sprites.width / obj->object.width;
	obj->col = 9;
	obj->row = obj->sprites.height / obj->object.height;
	obj->r = 8;
	obj->c = 0;
	return (obj);
}