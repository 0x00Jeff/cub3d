/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:35:18 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 17:40:17 by afatimi          ###   ########.fr       */
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
#include <clean.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel >> 3));
	*(unsigned int *)dst = color;
}

int	init_mlx_data(t_vars *vars)
{
	char *err;

	vars->mlx = mlx_init(M_WIDTH, M_HEIGHT, "I hate my self", 1);
	if (!vars->mlx)
	{
		err = (char *)mlx_strerror(mlx_errno);
		return (write(2, err, ft_strlen(err)), -1);
	}
	vars->image = mlx_new_image(vars->mlx, M_WIDTH, M_HEIGHT);
	if (!vars->image)
	{
		mlx_close_window(vars->mlx);
		err = (char *)mlx_strerror(mlx_errno);
		return (write(2, err, ft_strlen(err)), -1);
	}
	if (mlx_image_to_window(vars->mlx, vars->image, 0, 0) == -1)
	{
		mlx_close_window(vars->mlx);
		err = (char *)mlx_strerror(mlx_errno);
		return (write(2, err, ft_strlen(err)), -1);
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
	if (validator(&vars)) // TOOD : destroy map on all these errors
		return (-1);
	if (init_player_data(&vars))
	{
		free_textures(vars.texture);
		return (ft_putstr_fd("Error: could not initiate player data\n", 2), -1);
	}
	// TODO : free player data (texture) in case of an error
	install_hooks(&vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	free_textures(vars.texture);
	destroy_map(&vars.map);
	return (0);
}
