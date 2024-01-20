/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/20 22:28:20 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/hooks.h"
#include <stdio.h> // to delete;

void	install_hooks(t_vars *vars)
{
	mlx_key_hook(vars->mlx, print_key, vars);
	mlx_close_hook(vars->mlx, win_close, vars->mlx);
}

void	win_close(void *param)
{
	mlx_close_window(param);
}

void	print_key(mlx_key_data_t keydata, void *param)
{
	static int	start_x;
	static int	start_y;
	int x_step;
	int y_step;

	x_step = 50;
	y_step = 50;
	printf("key pressed : %d\n", keydata.key);
	if (keydata.key == MLX_KEY_ESCAPE)
		win_close(((t_vars *)param)->mlx);
	clear_screen(param, start_x, start_y);
	start_x += x_step * (keydata.key == MLX_KEY_RIGHT) * (start_x + x_step + 69 <= 1920) -
		x_step * (keydata.key == MLX_KEY_LEFT) * (start_x > 0);
	start_y += y_step * (keydata.key == MLX_KEY_DOWN) * (start_y + y_step + 69 <= 1080) -
		y_step * (keydata.key == MLX_KEY_UP) * (start_y > 0);
	draw_shit(param, start_x, start_y);
}
