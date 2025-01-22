/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:48:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/22 14:46:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"

static int	open_xpm_file(t_image *image, void *mlx_ptr, \
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

static int	load_images(t_game_schema *gs, void *mlx_ptr)
{
	t_image_info	images[5];
	int				nb_images;
	int				i;

	images[0] = (t_image_info){TILES_PATH, "tile"};
	images[1] = (t_image_info){PLAYER_PATH, "player"};
	images[2] = (t_image_info){FIRE_PATH, "fire"};
	images[3] = (t_image_info){BOAT_PATH, "boat"};
	images[4] = (t_image_info){TREE_PATH, "tree"};
	// images[5] = (t_image_info){TREE_PATH, "font"};
	nb_images = sizeof(images) / sizeof(*images);
	gs->schema.resources.nb_images = nb_images;
	gs->schema.resources.images = ft_calloc(nb_images, sizeof(t_image));
	i = -1;
	while (++i < nb_images)
		if (open_xpm_file(&gs->schema.resources.images[i], \
						mlx_ptr, images[i].path, images[i].name) != 0)
			return (-1);
	return (0);
}

int	load_game_schema(t_game_schema *gs, void *mlx_ptr)
{
	gs->schema.mlx_ptr = mlx_ptr;
	if (load_images(gs, mlx_ptr) != 0)
		return (-1);
	if (init_tiles(&gs->map.tiles, &gs->map.s_grid, &gs->map.floor, gs) != 0)
		return (-1);
	if (load_components((void *)gs, &gs->schema, &gs->map.o_grid) != 0)
		return (-1);
	((t_object *)&gs->map)->parent_location = (t_point *)&gs->camera.frame;
	return (0);
}

void	destroy_game_schema(t_game_schema **gs_r)
{
	t_map			*map;

	map = &(*gs_r)->map;
	destroy_object((void **)&map);
	free(*gs_r);
	*gs_r = NULL;
}

int	check_game_schema(t_game_schema *gs, char *map_path)
{
	return (load_map(&gs->map, map_path));
}

int	render_game_schema(t_game_schema *gs, t_image *frame)
{
	int		(*render)(void *, t_image *);

	update_object(schema_get_component_by_name(gs, "player"));
	update_camera(&gs->camera);
	render = ((t_object *)&gs->map)->render;
	if (render && render(&gs->map, frame) != 0)
		return (-1);
	return (0);
}

t_game_schema	*init_game_schema(void)
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
