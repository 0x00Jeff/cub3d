/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:54 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/23 22:23:42 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include <stdio.h> // to delete
#include <math.h>
#include <stdlib.h>

int		adjust_transparancy(int color, float trans);
void	draw_player(t_vars *vars, int start_x, int start_y)
{
	int size;
	for (size = 0; size <= DICK_SIZE; size++)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars -> image, start_x + j, start_y, 0xffffffff);
		start_y++;
	}
	for (; size >= 0; size--)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars -> image, start_x + j, start_y, 0xffffffff);
		start_y++;
	}
}

void do_graphics(void *param)
{
	(void)param;
	t_vars *vars;

	vars = param;
	(void)vars;
//	clear_screen(vars);
//	shoot_rays(vars, 10);
//	draw_square(param, 500, 500, 50, 0x00ff00ff);
}

void	clear_screen(t_vars *vars)
{
	int adjusted_color = adjust_transparancy(0xffffff, 0.5);
	for (int i = 0; i < (1920 / 69) + 1; i++)
	{
		for (int j = 0; j < (1080 / 69) + 1; j++)
			draw_square(vars, i * 69, j * 69, 69, ((i + j)% 2) ? adjusted_color : 0);
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
			protected_mlx_put_pixel(vars -> image, x + dx, y + dy, color);
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

void shoot_rays(t_vars *vars, int num)
{
	int i;

	i = 0;
	(void)num;
	int mouse_x, mouse_y;
	mlx_get_mouse_pos(vars -> mlx, &mouse_x, &mouse_y);

	draw_line(vars, M_WIDTH >> 1, M_HEIGHT >> 1, mouse_x, mouse_y);;
}

void draw_line(t_vars *vars, double x, double y, double target_x, double target_y)
{
	int dx = target_x - x;
	int dy = target_y - y;

	double step;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);

	double xinc = dx / step;
	double yinc = dy / step;

	int i = 0;
	while (i < step)
	{
		protected_mlx_put_pixel(vars -> image, roundf(x), roundf(y), 0xff0000ff);
		x += xinc;
		y += yinc;
		i++;
	}
}
