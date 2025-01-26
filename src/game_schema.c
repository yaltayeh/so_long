/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:48:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/26 19:08:44 by yaltayeh         ###   ########.fr       */
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
	t_image_info	images[6];
	int				nb_images;
	int				i;

	images[0] = (t_image_info){TILES_PATH, "tile"};
	images[1] = (t_image_info){PLAYER_PATH, "player"};
	images[2] = (t_image_info){FIRE_PATH, "fire"};
	images[3] = (t_image_info){BOAT_PATH, "boat"};
	images[4] = (t_image_info){TREE_PATH, "tree"};
	images[5] = (t_image_info){HEALTH_BAR_PATH, "health_bar"};
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
	if (init_tiles(&gs->map, gs) != 0)
		return (-1);
	if (load_components((void *)gs, &gs->map.o_grid) != 0)
		return (-1);
	((t_object *)&gs->map)->parent_location = &gs->camera.obj.relative_location;
	return (0);
}


void	swap_objects(t_object **obj1, t_object **obj2)
{
	t_object	*next;
	t_object	*prev;
	t_object	*tmp;

	printf("swap: '%s' '%s'\n", (char *)*obj1, (char *)*obj2);
	next = (*obj1)->next;
	prev = (*obj1)->prev;
	(*obj1)->next = (*obj2)->next;
	(*obj1)->prev = (*obj2)->prev;
	(*obj2)->next = next;
	(*obj2)->prev = prev;
	tmp = *obj1;
	*obj1 = *obj2;
	*obj2 = tmp;
}

void	 sort_components(t_game_schema *gs)
{
	t_object	**current;
	t_object	*tmp;
	t_object	*cursor;
	
	current = (t_object **)&gs->components.childrens;
	while (*current)
	{
		cursor = (*current)->next;
		while (cursor)
		{
			if ((*current)->relative_location.y > cursor->relative_location.y)
				swap_objects(current, &cursor);
			cursor = cursor->next;
		}
		tmp = (*current)->next;
		current = &tmp;
		break;
	}
}


t_game_schema	*init_game_schema(char *map_path)
{
	t_game_schema	*gschema;

	gschema = ft_calloc(1, sizeof(t_game_schema));
	if (!gschema)
		return (NULL);
	load_object(gschema);
	ft_strlcpy((char *)gschema, "game_schema", NAME_SIZE);

	load_object(&gschema->components);
	load_camera(&gschema->camera, gschema);

	((t_object *)gschema)->update = sort_components;
	((t_object *)gschema)->destroy = destroy_schema;
	gschema->schema.load_schema = load_game_schema;
	add_children(gschema, &gschema->camera);
	add_children(gschema, &gschema->components);
	if (load_map(&gschema->map, map_path) != 0)
	{
		destroy_object((void **)&gschema);
		return (NULL);
	}
	add_children(gschema, &gschema->map);

	t_object *cur;
	cur = ((t_object *)gschema)->childrens;
	while (cur)
	{
		printf("%s\n", (char *)cur);
		cur = cur->next;
	}
	
	return (gschema);
}
