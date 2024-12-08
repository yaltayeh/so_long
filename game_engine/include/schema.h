/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schema.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:38:11 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/08 17:03:02 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEMA_H
# define SCHEMA_H

# include "utils.h"
# include "object.h"

typedef struct  s_schema
{
	t_object	obj;
	struct s_resources
    {
        t_image **images;
        int		nb_images;
    }   resources;
    t_object    **components;
    int         nb_components;
	int			(*render)();
    int			(*load_schema)();
    int			(*destroy_schema)();
}	t_schema;



#endif