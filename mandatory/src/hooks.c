/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 14:05:48 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <draw.h>
#include <hooks.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void	hot_reload(void)
{
	puts("ye");
	if (g_module)
	{
		printf("before : g_module is @ %p\n", g_module);
		printf("before : g_do_graphics_ptr is @ %p\n", g_do_graphics_ptr);
		system("rm lib/lib.so ; make lib/lib.so; echo ");
		system("shasum lib/lib.so");
		g_do_graphics_ptr = NULL;
		printf("dlclose = %d\n", dlclose(g_module));
		g_module = NULL;
		puts("closing lib");
		printf("after : g_module is @ %p\n", g_module);
		printf("after : g_do_graphics_ptr is @ %p\n", g_do_graphics_ptr);
	}
	puts("opening lib");
	g_module = dlopen("lib/lib.so", RTLD_NOW);
	g_do_graphics_ptr = dlsym(g_module, "ft_do_graphics");
	printf("g_module is @ %p\n", g_module);
	printf("g_do_graphics_ptr is @ %p\n", g_do_graphics_ptr);
}

int	init_player_data(t_vars *vars)
{
	vars->player.map_needs_clearing = 69;
	vars->player.fov = 50;
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
//	while (!g_do_graphics_ptr || !g_module);
	g_do_graphics_ptr(param);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
		hot_reload();
}
