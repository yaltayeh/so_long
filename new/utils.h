/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:40:23 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/03 11:10:54 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#define NAME_SIZE 32

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_clip
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	layer;
}	t_clip;

#endif