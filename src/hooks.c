/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/21 19:02:10 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/hooks.h"
#include <stdio.h> // to delete;

void	install_hooks(t_vars *vars)
{
	mlx_loop_hook(vars->mlx, print_key, vars);
	mlx_close_hook(vars->mlx, win_close, vars->mlx);
}

void	win_close(void *param)
{
	mlx_close_window(param);
}

void	print_key(void *param)
{
	static int	start_x;
	static int	start_y;
	int x_step;
	int y_step;
	int needs_clearing;
	mlx_t *mlx = ((t_vars *)param) -> mlx;

	needs_clearing = (start_x << 8) + start_y;
	x_step = 10;
	y_step = 10;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		win_close(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		start_x += x_step * (start_x + x_step + 69 <= M_WIDTH);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		start_x -= x_step * (start_x > 0);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		start_y += y_step * (start_y + y_step + 69 <= M_HEIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		start_y -= y_step * (start_y > 0);
	if (needs_clearing != (start_x << 8 ) + start_y){
		clear_screen(param);
		draw_player(param, start_x, start_y);
	}
	printf("%.2f     \r", 1/mlx -> delta_time);
	fflush(stdout);
}
