/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/05 19:02:52 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/hooks.h"
#include <assert.h>
#include <math.h>
#include <stdio.h> // to delete;
#include <stdlib.h>
#define NOT_SYSTEM system

void	hot_reload(void)
{
	if (g_module)
		dlclose(g_module);
	g_module = NULL;
	NOT_SYSTEM("clear && make lib/lib.so && clear");
	g_module = dlopen("lib/lib.so", RTLD_NOW);
	g_do_graphics_ptr = dlsym(g_module, "do_graphics");
}

void init_data(t_vars *vars)
{
	vars->player.pos.x = 11.5;
	vars->player.pos.y = 5.5;
	vars->player.angle = 45;
	vars->player.map_needs_clearing = 69;
	vars->player.fov = 60;
	vars -> texture[NORTH] = mlx_load_png("resources/door.png");
	vars -> texture[SOUTH] = mlx_load_png("resources/greybricks.png");
	vars -> texture[EAST] = mlx_load_png("resources/figureOnWood.png");
	vars -> texture[WEST] = mlx_load_png("resources/crossOnWood.png");
}

void	install_hooks(t_vars *vars)
{
	init_data(vars);
	printf("install_hooks : player angle = %f\n", vars->player.angle);
	hot_reload();
	g_do_graphics_ptr(vars);
	mlx_loop_hook(vars->mlx, print_key, vars);
	mlx_close_hook(vars->mlx, win_close, vars->mlx);
}

void	win_close(void *param)
{
	mlx_close_window(param);
}

void	print_key(void *param)
{
	mlx_t	*mlx;

	mlx = ((t_vars *)param)->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		win_close(mlx);
	g_do_graphics_ptr(param);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
		hot_reload();
}
