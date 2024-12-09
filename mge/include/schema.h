/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schema.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:38:11 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 11:40:59 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEMA_H
# define SCHEMA_H

# include "utils.h"
# include "object.h"

typedef struct  s_schema
{
    void		*mlx_ptr;
	struct s_resources
    {
        t_image *images;
        int		nb_images;
    }           resources;
    t_object    **components;
    int         nb_components;
	int			(*component_cmp)();
    int         (*check_schema)();
    int			(*load_schema)();
    int			(*destroy_schema)();
}	t_schema;

int load_schema(t_schema *schema, void *data);
int render_schema(t_schema *schema, t_image *frame);
t_object	*get_component_by_name(t_schema *schema, const char *name);
t_image		*get_image_by_name(t_schema *schema, const char *name);

#endif