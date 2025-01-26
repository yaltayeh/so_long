/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:26:33 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/25 23:27:53 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEALTH_BAR_H
# define HEALTH_BAR_H

# include "sprites.h"
# include "schema.h"

enum    health_bar_types
{
	HB_SOLID_WHITE = 0,
	HB_BLUE_1 =	16,
	HB_GREEN_1,
	HB_GRAY_1,
	HB_RED_1,
	HB_PURPLE_1,
	HB_DARK_RED_1,
	HB_BUBBLE_RED = 32,
	HB_BUBBLE_GREEN,
	HB_BUBBLE_ORANGE,
	HB_BUBBLE_SELVER,
	HB_SMALL_BUBBLE_ORANGE = 48,
	HB_SMALL_BUBBLE_GREEN,
	HB_SMALL_BUBBLE_RED,
	HB_SMALL_BUBBLE_SELVER,
};

typedef struct	s_health_bar
{
	t_sprites	spr;
	t_object	*owner;
	t_clip		clip;
	int			*health_r;
	int			damge;
	t_clip		rec;
	
}	t_health_bar;

t_health_bar *init_health_bar(void *schema, void *owner, \
					int *health_r, int type);

#endif