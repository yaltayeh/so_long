/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:36:48 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/08 17:18:50 by yaltayeh         ###   ########.fr       */
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
# include "map.h"
# include "schema.h"

enum e_error_code
{
	SUCCESS,
	MAP_RECTANGULAR,
	MAP_SURROUNDED,
	FILE_OPEN,
	CHARACTER,
	MALLOC,
};

typedef struct s_game
{
	t_schema	schema;
	void		*mlx_ptr;
	void		*win_ptr;

	int			width;
	int			height;

	t_image		frame;
	
	t_clock		last_rander;
	t_clock		time;
}	t_game;

#endif
