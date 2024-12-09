/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:48:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 10:52:57 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int open_xpm_file(t_image *image, void *mlx_ptr, char *filename)
{
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, filename, &image->width, &image->height);
	if (!image->img_ptr)
		return (-1);
	if (load_image(image) != 0)
		return (-1);
	return (0);
}


static int	load_game_schema(t_game_schema *gschema)
{
	char	*images_path[5];
	int		nb_images;
	int		i;

	images_path[0] = TILEDS_PATH;
	images_path[1] = PLAYER_PATH;
	images_path[2] = FIRE_PATH;
	images_path[3] = BOAT_PATH;
	images_path[4] = TREE_PATH;
	nb_images = sizeof(images_path) / sizeof(*images_path);
	gschema->schema.resources.nb_images = nb_images;
	gschema->schema.resources.images = ft_calloc(nb_images, sizeof(t_image));
	i = 0;
	while (i < nb_images)
	{
		if (open_xpm_file(&gschema->schema.resources.images[i], \
							gschema->schema.mlx_ptr, images_path[i]) != 0)
			return (-1);
		i++;
	}
	
	return (0);
}

static int	destroy_game_schema(t_game_schema **gschema_r)
{
	return (0);
}

static int	check_game_schema(t_game_schema *gschema)
{
	return (0);
}


t_game_schema	*init_game_schema()
{
	t_game_schema	*gschema;

	gschema = ft_calloc(1, sizeof(t_game_schema));
	if (!gschema)
		return (NULL);
	if (load_schema(gschema) != 0)
	{
		free(gschema);
		return (NULL);
	}
	gschema->schema.check_schema = check_game_schema;
	gschema->schema.load_schema = load_game_schema;
	gschema->schema.destroy_schema = destroy_game_schema;
	gschema->schema.render_schema = render_game_schema;
	return (gschema);
}