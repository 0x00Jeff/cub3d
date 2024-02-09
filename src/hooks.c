/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/09 12:15:28 by afatimi          ###   ########.fr       */
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

int	init_player_data(t_vars *vars)
{
	static int	map[MAP_SIZE + 2][MAP_SIZE + 2] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	vars->map.m = (int *)map;
	vars->map.height = MAP_SIZE + 2;
	vars->map.width = MAP_SIZE + 2;
	vars->player.pos.x = 4.5;
	vars->player.pos.y = 5.5;
	vars->player.angle = 0;
	vars->player.map_needs_clearing = 69;
	vars->player.fov = 60;
	vars -> texture[NORTH] = mlx_load_png(vars -> map.tex[NORTH]);
	vars -> texture[SOUTH] = mlx_load_png(vars -> map.tex[SOUTH]);
	vars -> texture[EAST] = mlx_load_png(vars -> map.tex[EAST]);
	vars -> texture[WEST] = mlx_load_png(vars -> map.tex[WEST]);
	return ((!!vars -> texture[NORTH] + !!vars -> texture[SOUTH] + \
		!!vars -> texture[EAST] + !!vars -> texture[WEST]) != 4);
}

void	install_hooks(t_vars *vars)
{
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
