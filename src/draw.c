/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:54 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/21 18:53:34 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include <stdio.h> // to delete

int		adjust_transparancy(int color, float trans);
void	draw_shit(t_vars *vars, int start_x, int start_y)
{
	for (int i = 0; i < 69; i++)
	{
		for (int j = 0; j < 69; j++)
			mlx_put_pixel(vars -> image, start_x + i, start_y + j, 0xffffff);
	}
}

void	clear_screen(t_vars *vars)
{
	for (int i = 0; i < (1920 / 69) + 1; i++)
	{
		for (int j = 0; j < (1080 / 69) + 1; j++)
			draw_square(vars, i * 69, j * 69, 69, ((i + j)% 2) ? 0xffffffff : 0);
	}
}

void	draw_square(t_vars *vars, int x, int y, int size, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			protected_mlx_put_pixel(vars -> image, x + dx, y + dy, adjust_transparancy(color, 0.5));
			dx++;
		}
		dy++;
	}
}

void protected_mlx_put_pixel(mlx_image_t *image, int x, int y, int color)
{
	if (x < 0 | x >= M_WIDTH | y < 0 | y >= M_HEIGHT)
		return;
	mlx_put_pixel(image, x, y, color);
}
