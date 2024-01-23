/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:35:18 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/23 19:50:25 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/test.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int	adjust_transparancy(int color, float trans)
{
	if (trans < 0)
		trans = -trans;
	if (trans > 1)
		trans = 1;
	return ((color << 8) + (int)(0xff - (trans * 0xff)));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr +
		(y * data->line_length + x * (data->bits_per_pixel >> 3));
	*(unsigned int *)dst = color;
}

int	init_mlx_data(t_vars *vars)
{
	vars->mlx = mlx_init(M_WIDTH, M_HEIGHT, "I hate my self", 1);
	if (!vars->mlx)
	{
		fprintf(stderr, "%s\n", (mlx_strerror(mlx_errno)));
		return (-1);
	}
	vars->image = mlx_new_image(vars->mlx, M_WIDTH, M_HEIGHT);
	if (!vars->image)
	{
		mlx_close_window(vars->mlx);
		fprintf(stderr, "%s\n", (mlx_strerror(mlx_errno)));
		return (-1);
	}
	if (mlx_image_to_window(vars->mlx, vars->image, 0, 0) == -1)
	{
		mlx_close_window(vars->mlx);
		fprintf(stderr, "%s\n", (mlx_strerror(mlx_errno)));
		return (-1);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;

	if (init_mlx_data(&vars) == -1)
		return (-1);

	install_hooks(&vars);
//	clear_screen(&vars);
//	draw_player(&vars, DICK_SIZE, 0);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (0);
}
