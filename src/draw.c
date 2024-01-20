/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:54 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/20 22:28:21 by afatimi          ###   ########.fr       */
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
		{
			mlx_put_pixel(vars -> image, start_x + i, start_y + j, adjust_transparancy(0xffffff, 0.5));
		}
	}
}

void	clear_screen(t_vars *vars, int start_x, int start_y)
{
	(void)start_x;
	(void)start_y;
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
			mlx_put_pixel(vars -> image, i, j, 0xff0000);
	}
}
