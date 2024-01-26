/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/26 14:30:17 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/hooks.h"
#include <stdio.h> // to delete;
#include <stdlib.h>
#include <math.h>

void hot_reload()
{
	if (module)
		dlclose(module);
	module = NULL;
	system("make lib/lib.so");
	module = dlopen("lib/lib.so", RTLD_NOW);
	do_graphics_ptr = dlsym(module, "do_graphics");
}

void	install_hooks(t_vars *vars)
{
	// TODO : move these to some kinda init_player function
	// specially the first line for now, the second one is meh
	//vars -> player.mouse_needs_clearing = 0;
	vars -> player.pos.x = PLAYER_SIZE;
	vars -> player.angle = 45;
	vars -> player.map_needs_clearing = 69;
	printf("install_hooks : player angle = %f\n", vars -> player.angle);
	hot_reload();
	do_graphics_ptr(vars);
	mlx_loop_hook(vars->mlx, print_key, vars);
	mlx_close_hook(vars->mlx, win_close, vars->mlx);
}

void	win_close(void *param)
{
	mlx_close_window(param);
}

void	print_key(void *param)
{
	mlx_t *mlx = ((t_vars *)param) -> mlx;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		win_close(mlx);
	//if (needs_clearing != (start_x << 8) + start_y){
		//do_graphics_ptr(param);
		////clear_screen(param);
		////draw_player(param, start_x, start_y);
		//;
	//}
	do_graphics_ptr(param);

	if (mlx_is_key_down(mlx, MLX_KEY_R))
		hot_reload();
}
