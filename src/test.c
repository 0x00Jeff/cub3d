/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:35:18 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 21:00:23 by afatimi          ###   ########.fr       */
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

void check_leaks()
{
	system("leaks cub3D");
}

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

	atexit(check_leaks);
	if (argc != 2)
		err_and_exit("Usage: cub3D map.cub\n");
	if (init_mlx_data(&vars) == -1)
		return (-1);
	if (parser(&vars, argv[1]))
	{
		destroy_map(&vars.map);
		// TODO : destroy_mlx_image();
		return (-1);
	}
	if (validator(&vars)){ // TOOD : destroy map on all these errors
		destroy_map(&vars.map);
		// TODO : destroy_mlx_image();
		return (-1);
	}
	if (init_player_data(&vars))
	{
		destroy_map(&vars.map);
		// TODO : destroy_mlx_image();
		free_textures(vars.texture);
		err_and_exit("Error: could not initiate player data\n");
	}
	// TODO : free player data (texture) in case of an error
	install_hooks(&vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	free_textures(vars.texture);
	free_texture_names((char **)&vars.map.tex);
	free(vars.map.data);
	destroy_map(&vars.map);
	return (0);
}
