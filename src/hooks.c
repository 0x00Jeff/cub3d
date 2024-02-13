/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 19:49:23 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/hooks.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

int	init_player_data(t_vars *vars)
{
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
	do_graphics(vars);
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
	do_graphics(param);
}
