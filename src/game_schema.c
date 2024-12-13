/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:48:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/12 19:17:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"


static int open_xpm_file(t_image *image, void *mlx_ptr, \
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

int	load_game_schema(t_game_schema *gs, void *mlx_ptr)
{
	char	*images_path[5];
	char	*images_name[5];
	int		nb_images;
	int		i;

	images_path[0] = TILEDS_PATH;
	images_name[0] = "tiled";
	images_path[1] = PLAYER_PATH;
	images_name[1] = "player";
	images_path[2] = FIRE_PATH;
	images_name[2] = "fire";
	images_path[3] = BOAT_PATH;
	images_name[3] = "boat";
	images_path[4] = TREE_PATH;
	images_name[4] = "tree";

	nb_images = sizeof(images_path) / sizeof(*images_path);
	gs->schema.resources.nb_images = nb_images;
	gs->schema.resources.images = ft_calloc(nb_images, sizeof(t_image));
	i = 0;
	while (i < nb_images)
	{
		if (open_xpm_file(&gs->schema.resources.images[i], \
						mlx_ptr, images_path[i], images_name[i]) != 0)
			return (-1);
		i++;
	}
	if (init_tiled_blocks(&gs->map.tileds, &gs->map.s_map, &gs->map.tiled_data, gs) != 0)
		return (-1);
	if (load_components((void *)gs, &gs->map.o_map) != 0)
		return (-1);
	((t_object *)&gs->map)->parent_location = (t_point *)&gs->camera.frame;
	return (0);
}

int	destroy_game_schema(t_game_schema **gs_r)
{
	(void)gs_r;
	return (0);
}

int	check_game_schema(t_game_schema *gs, char *map_path)
{
	int	stat;

	stat = load_map(&gs->map, map_path);
	ft_printf("%s: %d\n", __func__, stat);
	return (stat);
}


int	render_game_schema(t_game_schema *gs, t_image *frame)
{
	int		(*render)(void *, t_image *);
	// void	(*update)(void *);

	update_object(schema_get_component_by_name(gs, "player"));
	update_camera(&gs->camera);
	// update = ((t_object *)&gs->map)->update;
	// if (update)
	// 	update(&gs->map);
	render = ((t_object *)&gs->map)->render;
	if (render && render(&gs->map, frame) != 0)
		return (-1);
	return (0);
}

t_game_schema	*init_game_schema()
{
	t_game_schema	*gschema;

	gschema = ft_calloc(1, sizeof(t_game_schema));
	if (!gschema)
		return (NULL);
	gschema->camera.schema = gschema;
	gschema->schema.check_schema = check_game_schema;
	gschema->schema.render_schema = render_game_schema;
	gschema->schema.load_schema = load_game_schema;
	gschema->schema.destroy_schema = destroy_game_schema;
	return (gschema);
}