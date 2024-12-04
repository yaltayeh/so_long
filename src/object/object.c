/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:57:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/04 12:09:53 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_sprites(t_sprite *spr, char *sprites_path)
{

	spr->image.img_ptr = mlx_xpm_file_to_image(spr->obj.mlx_ptr, sprites_path, 
								&spr->image.width, &spr->image.height);
	if (!spr->image.img_ptr)
		return (-1);
	if (load_image(&spr->image) == -1)
		return (-1);
	return (0);	
}

// void *destroy_object(t_object	**obj)
// {
// 	if (*obj)
// 	{
// 		if ((*obj)->sprites.img_ptr)
// 			mlx_destroy_image((*obj)->mlx_ptr, (*obj)->sprites.img_ptr);
// 		if ((*obj)->object.img_ptr)
// 			mlx_destroy_image((*obj)->mlx_ptr, (*obj)->object.img_ptr);
// 		free(*obj);
// 	}
// 	*obj = NULL;
// 	return (NULL);
// }


t_sprite	*init_character(void *mlx_ptr, char *sprites_path)
{
	t_sprite	*spr;

	spr = ft_calloc(1, sizeof(t_sprite));
	if (!spr)
		return (NULL);
	spr->obj.mlx_ptr = mlx_ptr;

	load_sprites(spr, sprites_path);
	// if (load_sprites(spr, sprites_path) == -1)
	// 	return (destroy_object(&obj));
	spr->image.width = 64;
	spr->image.height = 64;
	spr->col = spr->image.width / spr->image.width;
	spr->col = 9;
	spr->row = spr->image.height / spr->image.height;
	spr->r = 8;
	spr->c = 0;
	return (spr);
}