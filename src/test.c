/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:35:18 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 18:04:46 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <draw.h>
#include <parse.h>
#include <stdio.h>
#include <stdlib.h>
#include <test.h>
#include <time.h>
#include <unistd.h>
#include <libft.h>
#include <validation.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel >> 3));
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

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
		return (ft_putstr_fd("Usage: cub3D map.cub\n", 2), -1);
	if (init_mlx_data(&vars) == -1)
		return (-1);
	if (parser(&vars, argv[1]))
		return (-1);
	if (validator(&vars))
		return (-1);
	if (init_player_data(&vars))
		return (ft_putstr_fd("Error: could not initiate player data\n", 2), -1);
	install_hooks(&vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (0);
}
