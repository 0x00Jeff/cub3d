/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:11:14 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/10 21:34:06 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unused.h>

void	draw_point(t_vars *vars, t_vector pos, int point_size, int color) //  DEBUG
{
	SKIP
	int size;
	long start_x;
	long start_y;

	start_x = pos.x * TILE_SIZE;
	start_y = pos.y * TILE_SIZE - (point_size >> 1);
	for (size = 0; size <= point_size; size++)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars->image, (start_x + j), start_y, color);
		start_y++;
	}
	for (; size >= 0; size--)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars->image, (start_x + j), start_y, color);
		start_y++;
	}
}

void	draw_player(t_vars *vars)
{
	SKIP
	draw_point2(vars, vars->player.pos.x * TILE_SIZE * MAP_SCALE_FACTOR,
		vars->player.pos.y * TILE_SIZE * MAP_SCALE_FACTOR, 4, PRIV_ESC);
}

void	draw_point2(t_vars *vars, int x, int y, int point_size, int color)
{
	SKIP
	int	size;
	int	start_x;
	int	start_y;

	start_x = x;
	start_y = y - point_size;
	for (size = 0; size <= point_size; size++)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars->image, (start_x + j), start_y, color);
		start_y++;
	}
	for (; size >= 0; size--)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars->image, (start_x + j), start_y, color);
		start_y++;
	}
}

void	draw_line(t_vars *vars, t_vector pos, t_vector *target_pos, int color)
{
	SKIP
	t_vector	delta;
	t_vector	inc;
	double		step;
	int			i;

	i = 0;
	delta.x = target_pos->x - pos.x;
	delta.y = target_pos->y - pos.y;
	if (abs((int)delta.x) > abs((int)delta.y))
		step = delta.x;
	else
		step = delta.y;
	if (step < 0)
		step *= -1;
	inc.x = delta.x / step;
	inc.y = delta.y / step;
	while (i < step)
	{
		protected_mlx_put_pixel(vars->image, roundf(pos.x), roundf(pos.y),
			color);
		vect_add(&pos, &inc);
		i++;
	}
}

void	draw_map(t_vars *vars)
{
	SKIP
	for (size_t y = 0; y < vars->map.height; y++)
	{
		for (size_t x = 0; x < vars->map.width; x++)
		{
			if (vars->map.m[y * vars->map.width + x] == 1)
			{
				// TODO : might replace the map check with get_map_item not to segfault if checking outside of the map
				draw_square(vars,
					(t_ivector){x, y},
					TILE_SIZE * MAP_SCALE_FACTOR,
					adjust_transparancy(0x9b734f, 0.2));
			}
		}
	}
}

void	clear_screen(t_vars *vars)
{
	int	color;

	color = adjust_transparancy(0xffffff, 0.5);
	for (int i = 0; i < (1920 / TILE_SIZE) + 1; i++)
	{
		for (int j = 0; j < (1080 / TILE_SIZE) + 1; j++)
			draw_square(vars,
						(t_ivector){i, j},
						TILE_SIZE,
						((i + j) % 2) ? color : 0);
	}
}
