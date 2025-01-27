/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_schema.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:48:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/27 08:57:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_schema.h"

int	open_xpm_file(t_image *image, void *mlx_ptr, \
						char *filename, const char *img_name);
t_object	*pop_player(t_object *components);

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

void	update_game_schema(t_game_schema *gs)
{
	t_object	*player;
	t_object	*current;
	t_object	*prev;
	t_object	*components;

	components = &gs->components;
	player = pop_player(components);
	if (!player)
		return ;
	current = components->childrens;
	prev = NULL;
	while (current)
	{
		if (current->relative_location.y < player->relative_location.y)
		{
			if (!prev)
				add_children(components, player);
			else
			{
				player->next = current;
				prev->next = player;
			}
			return ;
		}
		prev = current;
		current = current->next;
	}
	if (prev)
		prev->next = player;
}

t_game_schema	*init_game_schema()
{
	t_game_schema	*gschema;

	gschema = ft_calloc(1, sizeof(t_game_schema));
	if (!gschema)
		return (NULL);
	load_object(gschema);
	ft_strlcpy((char *)gschema, "game_schema", NAME_SIZE);
	load_object(&gschema->components);
	load_camera(&gschema->camera, gschema);
	load_map(&gschema->map);
	((t_object *)gschema)->update = update_game_schema;
	((t_object *)gschema)->destroy = destroy_schema;
	gschema->schema.load_schema = load_game_schema;
	add_children(gschema, &gschema->camera);
	add_children(gschema, &gschema->components);
	add_children(gschema, &gschema->map);	
	return (gschema);
}
