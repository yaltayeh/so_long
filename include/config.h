/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:11:43 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/30 11:30:01 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "X11/keysym.h"

# define WIN_WIDTH  1280
# define WIN_HEIGHT 768

# ifndef TILEDS_PATH
#  define TILES_PATH "textures/tile.xpm"
# endif

# ifndef PLAYER_PATH
#  define PLAYER_PATH "textures/lumberjack.xpm"
# endif
# ifndef PLAYER_SPEED
#  define PLAYER_SPEED 6 
# endif

# ifndef FIRE_PATH
#  define FIRE_PATH "textures/bonfire.xpm"
# endif

# ifndef BOAT_PATH
#  define BOAT_PATH "textures/boat_64x64.xpm"
# endif

# ifndef TREE_PATH
#  define TREE_PATH "textures/trees_56x94.xpm"
# endif

# ifndef BANNER_PATH
#  define BANNER_PATH "textures/banner.xpm"
# endif




# define WASD

# ifdef __linux__
#  define DELAY		5000
#  define KEY_SPACE 0x0020
#  define KEY_ESC	0xff1b
#  ifdef WASD
#   define KEY_UP		0x0077
#   define KEY_DOWN		0x0073
#   define KEY_RIGHT	0x0064
#   define KEY_LEFT		0x0061
#  else
#   define KEY_UP		0xff52
#   define KEY_DOWN		0xff54
#   define KEY_RIGHT	0xff53
#   define KEY_LEFT		0xff51
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