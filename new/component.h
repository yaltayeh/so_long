/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 23:02:04 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/03 11:26:49 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPONENT_H
# define COMPONENT_H

#include "stdlib.h"
#include <stddef.h>

enum	OPTION_TYPES
{
	OPT_TYPE_INT,
	OPT_TYPE_LONG,
	OPT_TYPE_PTR,
	OPT_TYPE_STRING,
};

typedef	struct s_option
{
	const char *name;
	size_t		offset;
	int			type;
	union
	{
		int64_t		i64;
		void		*ptr;
		const char	*str;
	}	default_val;
}	t_option;


typedef	struct s_class
{
	const	t_option *options;
}	t_class;

typedef struct s_component
{
	const char	*name;
	t_class		*class;
	size_t		size;
	void		(*render)();
	int			(*init)();
	int			(*uninit)();
}	t_component;

typedef	struct s_component_context
{
	const t_component	*component;
	void				*priv;
}	t_component_context;

t_component_context	*init_component(const char *name);
void				render_component(t_component_context *ctx);
void				print_component_value(t_component_context *ctx);


#define COMPONENT_DEFINE_CLASS(name)	\
	static t_class 	name##_class = {	\
		.options = name##_options,		\
	};									\

#endif