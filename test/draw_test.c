/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:39:17 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/16 10:00:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

typedef struct s_data
{
	void *mlx_ptr;
	void *win_ptr;
	void *frame;
	int width;
	int height;
}	t_data;


int	render(t_data *data)
{
	int	bpp, size_line, endian;
	int	x;
	int	y;
	int	*buffer;

	static double a = 100, b = 50;
	buffer = (int *)mlx_get_data_addr(data->frame, &bpp, &size_line, &endian);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			int	color = 0xffffff;
			int _x = x - 100;
			int _y = y - 100;
			if ((_x * _x * 1.f) / (a * a) + (_y * _y * 1.f)/ (b * b) <= 1)
				color = 0xff0000;
			buffer[y * data->height + x] = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->frame, 0,0);
	return (0);
}

int main()
{
	t_data	data;

	data.width = 500;
	data.height = 500;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "test");
	if (!data.win_ptr)
		return (1);
	data.frame = mlx_new_image(data.mlx_ptr, data.width, data.height);
	if (!data.frame)
		return (1);
	mlx_loop_hook(data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}