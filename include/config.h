/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:11:43 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 07:36:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

#include "X11/keysym.h"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 650

# ifndef TILEDS_PATH
#  define TILES_PATH "textures/tile.xpm"
# endif
# ifndef TILED_DELEY
#  define TILED_DELEY 4
# endif
# ifndef TSIZE
#  define TSIZE 64
# endif

# ifndef PLAYER_PATH
#  define PLAYER_PATH "textures/lumberjack.xpm"
# endif
# ifndef PLAYER_DELEY
#  define PLAYER_DELEY 1
# endif
# ifndef PLAYER_SPEED
#  define PLAYER_SPEED 4
# endif

# ifndef FIRE_PATH
#  define FIRE_PATH "textures/bonfire.xpm"
# endif
# ifndef FIRE_DELEY
#  define FIRE_DELEY 1
# endif

# ifndef BOAT_PATH
#  define BOAT_PATH "textures/boat_64x64.xpm"
# endif
# ifndef BOAT_DELEY
#  define BOAT_DELEY 2
# endif

# ifndef TREE_PATH
#  define TREE_PATH "textures/trees_56x94.xpm"
# endif
# ifndef TREE_DELEY
#  define TREE_DELEY 1
# endif

# define WASD

# ifdef __linux__
#  define DELAY		11500
#  define KEY_SPACE XK_space
#  define KEY_ESC	XK_Escape
#  ifdef WASD
#   define KEY_UP		XK_w
#   define KEY_DOWN		XK_s
#   define KEY_RIGHT	XK_d
#   define KEY_LEFT		XK_a
#  else
#   define KEY_UP		XK_Up
#   define KEY_DOWN		XK_Down
#   define KEY_RIGHT	XK_Right
#   define KEY_LEFT		XK_Left
#  endif
# else
#  define DELAY		400
#  define KEY_SPACE 0x31
#  define KEY_ESC	0x35
#  ifdef WASD
#   define KEY_UP		0x0d
#   define KEY_DOWN		0x01
#   define KEY_RIGHT	0x02
#   define KEY_LEFT		0x00
#  else
#   define KEY_UP		0x7e
#   define KEY_DOWN		0x7d
#   define KEY_RIGHT	0x7c
#   define KEY_LEFT		0x7b
#  endif
# endif
#endif