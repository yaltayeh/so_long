/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:29:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/06 21:12:59 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "sprites.h"

enum e_directions
{
	BACK,
	LEFT,
	FRONT,
	RIGHT
};

enum e_move_type
{
	SPELLCAST,
	THRUST,
	WALK,
	SLASH_128
};

typedef struct s_player
{
	t_sprites			spr;
	t_point				loc;
	t_clip				clip;
	int					logs_count;
	enum e_move_type	movement;
	enum e_directions	direction;
	int					is_walk;
	int					speed;
}	t_player;

int	update_player(t_player *player);
int	load_player(t_player *player, void *mlx_ptr);

#endif