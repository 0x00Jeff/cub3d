/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:35:18 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/19 20:15:02 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr +
		(y * data->line_length + x * (data->bits_per_pixel >> 3));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *data, int x, int y, int size, int color)
{
	int	dx;
	int	dy;

	srand(time(NULL));
	(void)color;
	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			my_mlx_pixel_put(data, x + dx, y + dy, rand());
			dx++;
		}
		dy++;
	}
}

void draw_random(t_data *data, int start_x, int start_y, int size, int color)
{
	int x;
	int y;

	for(y = 0; y < (1080 / 69); y++)
	{
		for(x = 0; x < (1920 / 69); x++)
		{
			printf("x = %d, ", x);
			draw_square(data, start_x + x * 69, start_y + y * 69, size, color);
		}
			draw_square(data, start_x + x * 69, start_y + y * 69, 60, color);
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "henlo");
	draw_random(&img, 0, 0, 60, 0xff0063);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
