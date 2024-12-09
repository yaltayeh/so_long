/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:36:48 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/09 07:59:26 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <ft_stack.h>
# include <fcntl.h>
# include "config.h"
# include "mge.h"

enum e_error_code
{
	SUCCESS,
	MAP_RECTANGULAR,
	MAP_SURROUNDED,
	FILE_OPEN,
	CHARACTER,
	MALLOC,
};

typedef struct s_game_schema
{
	t_schema	schema;
	t_map_data	*o_map;
}	t_game_schema;

typedef struct s_game
{
	t_schema	*schema;

	void		*win_ptr;
	int			width;
	int			height;
	t_image		frame;
	
	t_clock		last_rander;
	t_clock		time;
}	t_game;

int	load_game_schema(t_game_schema *gschema);
int	destroy_game_schema(t_game_schema **gschema_r);

#endif
