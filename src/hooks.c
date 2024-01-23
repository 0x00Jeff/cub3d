/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/23 21:35:09 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/hooks.h"
#include <stdio.h> // to delete;
#include <stdlib.h>

void hot_reload(t_vars *vars)
{
	(void)vars;
	system("make");
	while (!module)
		module = dlopen("lib/lib.so", RTLD_NOW);
	do_graphics_ptr = dlsym(module, "do_graphics");
	do_graphics_ptr(vars);
	dlclose(module);
	module = NULL;
}

void	install_hooks(t_vars *vars)
{
	hot_reload(vars);
	mlx_loop_hook(vars->mlx, print_key, vars);
	mlx_close_hook(vars->mlx, win_close, vars->mlx);
}

void	win_close(void *param)
{
	mlx_close_window(param);
}

void	print_key(void *param)
{
	static int	start_x = DICK_SIZE;
	static int	start_y;
	int x_step;
	int y_step;
	int needs_clearing;
	mlx_t *mlx = ((t_vars *)param) -> mlx;

//	if (!do_graphics_ptr)
//		hot_reload(param);

	needs_clearing = (start_x << 8) + start_y;
	x_step = 10;
	y_step = 10;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		win_close(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		start_x += x_step * (start_x + x_step + DICK_SIZE <= M_WIDTH);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		start_x -= x_step * (start_x > DICK_SIZE);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		start_y += y_step * (start_y + y_step + DICK_SIZE * 2<= M_HEIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		start_y -= y_step * (start_y > 0);
	if (needs_clearing != (start_x << 8) + start_y){
		do_graphics_ptr(param);
		//clear_screen(param);
		//draw_player(param, start_x, start_y);
		;
	}
	//do_graphics_ptr(param);

	if (mlx_is_key_down(mlx, MLX_KEY_R))
		hot_reload(param);
}
