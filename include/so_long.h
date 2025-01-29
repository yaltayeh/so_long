/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:36:48 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/29 08:06:36 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <libft.h>
# include "map.h"
# include "game_schema.h"

typedef struct s_game
{
	t_game_schema	*gs;
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
	t_player		*player;
	t_image			frame;
	t_clock			last_rander;
	t_clock			time;
}	t_game;

int	ft_islower(int c);
int	ft_isupper(int c);

#endif
