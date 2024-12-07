/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:36:48 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/06 21:14:11 by yaltayeh         ###   ########.fr       */
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
# include "player.h"
# include "map.h"

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
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
	t_map			map;
	t_player		player;
	t_image			frame;
	t_clock			last_rander;
	t_clock			time;
}	t_game;

#endif
