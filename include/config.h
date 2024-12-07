/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:11:43 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/07 17:31:19 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CONFIG_H
# define CONFIG_H

# ifndef TILEDS_PATH
#  define TILEDS_PATH "textures/tiled.xpm"
# endif
# ifndef TILED_DELEY
#  define TILED_DELEY 4
# endif
# ifndef TILED_SIZE
#  define TILED_SIZE 64
# endif

# ifndef PLAYER_PATH
#  define PLAYER_PATH "textures/lumberjack.xpm"
# endif
# ifndef PLAYER_DELEY
#  define PLAYER_DELEY 1
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
#  define TREE_DELEY 2
# endif


# ifdef __linux__
#  define DELAY		12500
#  define KEY_UP		XK_Up
#  define KEY_DOWN	XK_Down
#  define KEY_RIGHT	XK_Right
#  define KEY_LEFT	XK_Left
# else
#  define DELAY		500
#  define KEY_UP		126
#  define KEY_DOWN	125
#  define KEY_RIGHT	124
#  define KEY_LEFT	123
# endif

# define ESC_KEYCODE 53

#endif