/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:36:48 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/02 11:52:49 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <libft.h>
# include "map.h"
# include "game_schema.h"
# include <math.h>

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

int		ft_islower(int c);
int		ft_isupper(int c);

int		is_surround_boat(t_game *game);
void	ride_boat(t_game *game);
void	end_program(void *_game, int exit_status);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		rander(t_game *game);
int		cross_button(t_game *game);

#endif