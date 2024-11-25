/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:55:15 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/25 20:33:29 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprites	*sprites_parser(const char *spr_path)
{
	int	fd;

	fd = open(spr_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	
}
