/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schema.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:38:11 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/16 09:20:25 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEMA_H
# define SCHEMA_H

# include "utils.h"
# include "object.h"

typedef struct s_schema
{
	void	*mlx_ptr;
	struct s_resources
	{
		t_image	*images;
		int		nb_images;
	}			resources;
	t_object	**components;
	int			nb_components;
	int			(*component_cmp)();
	int			(*check_schema)();
	int			(*render_schema)();
	int			(*load_schema)();
	int			(*destroy_schema)();
}	t_schema;

int			load_schema(void *_schema, void *data);
int			render_schema(void *_schema, t_image *frame);
int			check_schema(void *_schema, void *data);
void		destroy_schema(void **_schema);
t_object	*schema_get_component_by_name(void *_schema, const char *name);
t_object	*schema_get_component_by_loacation(void *_schema, t_point loacation);
t_image		*schema_get_image_by_name(void *_schema, const char *name);

#endif