/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:11:10 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/31 19:58:54 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:54 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/31 17:11:04 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/vectors.h"
#include <math.h>
#include <stdio.h> // to delete
#include <stdlib.h>
#include <time.h>

int	adjust_transparancy(int color, float trans)
{
	if (trans < 0)
		trans = -trans;
	if (trans > 1)
		trans = 1;
	return ((color << 8) + (int)(0xff - (trans * 0xff)));
}

void	draw_player(t_vars *vars)
{
	int	size;
	double	start_x;
	double	start_y;

	start_x = vars->player.pos.x * TILE_SIZE;
	start_y = vars->player.pos.y * TILE_SIZE - PLAYER_SIZE;
	for (size = 0; size <= PLAYER_SIZE; size++)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars->image, (start_x + j), start_y, PRIV_ESC);
		start_y++;
	}
	for (; size >= 0; size--)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars->image, (start_x + j), start_y, PRIV_ESC);
		start_y++;
	}
}

void	inc_pos_vect(t_vector *vect, double factor, double angle)
{
	vect->x += factor * cos(angle * (M_PI / 180));
	vect->y += factor * sin(angle * (M_PI / 180));
}

void	move_player(t_vars *vars)
{
	void		*mlx;
	t_player	*player;

	mlx = vars->mlx;
	player = &vars->player;
	player->map_needs_clearing = player->pos.x * 10000 + \
		player->pos.y;
	player->old_angle = player->angle;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->angle += ROT_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->angle -= ROT_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		inc_pos_vect(&player->pos, -SPEED, player->angle - 90);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		inc_pos_vect(&player->pos, -SPEED, player->angle + 90);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		inc_pos_vect(&player->pos, -SPEED, player->angle);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
		inc_pos_vect(&player->pos, SPEED, player->angle);
	return ;
}

int	needs_clearing(t_vars *vars)
{
	t_player	*player;

	player = &vars->player;
	if (player->map_needs_clearing != player->pos.x * 10000 + player->pos.y)
		return (1);
	if (player->angle != player->old_angle)
	{
		player->old_angle = player->angle;
		return (1);
	}
	return (0);
}

void	draw_map(t_vars *vars)
{
	static int map[MAP_SIZE][MAP_SIZE] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	vars -> map.m = (int *)map;
	vars -> map.height = MAP_SIZE;
	vars -> map.width = MAP_SIZE;

	for (int y = 0; y < vars -> map.height; y++)
	{
		for (int x = 0; x < vars -> map.width; x++)
		{
			if (vars -> map.m[y * MAP_SIZE + x] == 1)
				draw_square(vars, (t_ivector){x, y}, 0x00ff00ff);
		}
	}
}

void display_fps(t_vars *vars)
{
	static double old_time = 0;

	int fps = (int)(1 / vars->mlx->delta_time);
	if (mlx_get_time() - old_time > 0.1)
	{
		printf("fps: %d    \r", fps);
		fflush(stdout);
		old_time = mlx_get_time();
	}
}

void	do_graphics(t_vars *vars)
{
	display_fps(vars);
	move_player(vars);
	if (!needs_clearing(vars))
		return ;
	clear_screen(vars);
	draw_map(vars);
	draw_player(vars);
	shoot_rays(vars, RAYS_NUM, RAY_LEN);
}

void	clear_screen(t_vars *vars)
{
	int	adjusted_color;

	adjusted_color = adjust_transparancy(0xffffff, 0.5);
	for (int i = 0; i < (1920 / TILE_SIZE) + 1; i++)
	{
		for (int j = 0; j < (1080 / TILE_SIZE) + 1; j++)
			draw_square(vars, (t_ivector){i, j}, ((i + j)
						% 2) ? adjusted_color : 0);
	}
	return;
}

void	draw_square(t_vars *vars, t_ivector pos, int color)
{
	t_ivector delta;
	int size;

	size = TILE_SIZE;
	delta.y = 0;
	while (delta.y < size)
	{
		delta.x = 0;
		while (delta.x < size)
		{
			protected_mlx_put_pixel(vars->image, pos.x * TILE_SIZE + delta.x, pos.y * TILE_SIZE+ delta.y, color);
			delta.x++;
		}
		delta.y++;
	}
}

void	protected_mlx_put_pixel(mlx_image_t *image, int x, int y, int color)
{
	if ((x < 0) | (x >= M_WIDTH) | (y < 0) | (y >= M_HEIGHT))
		return ;
	mlx_put_pixel(image, x, y, color);
}


void	shoot_rays(t_vars *vars, int num, int factor)
{
	double		i;
	double		angle;
	t_vector	visual_player;
	t_ray		ray;
	(void)factor;
	int			color;
	color = adjust_transparancy(0xff0000, 0);

	vect_assign(&visual_player, &vars -> player.pos);
	vect_scale(&visual_player, TILE_SIZE);
	angle = vars->player.angle - (vars->player.fov >> 1);
	vect_assign(&ray.from, &visual_player);
	i = 0;

	while (i < num)
	{
		vect_assign(&ray.to, &visual_player);
		shoot_ray(vars, &ray, angle, color);
		angle += (double)vars -> player.fov / num;
		i++;
	}
}

void	shoot_ray(t_vars *vars, t_ray *ray, double angle, int color)
{
	t_vector	direction;
	inc_pos_vect(&ray -> to, RAY_LEN, angle);
	vect_sub(&ray -> to, &ray -> from);

	vect_assign(&direction, &ray -> to);
	double dist_to_hit = dda(vars, &direction, -angle);
	//double dist_to_hit = 1;

	vect_scale(&ray -> to, dist_to_hit);
	vect_add(&ray -> to, &ray -> from);
	draw_line(vars, ray -> from, &ray -> to, color);
}

void	draw_point(t_vars *vars, t_vector pos, int point_size, int color) //  DEBUG
{
	int size;
	long start_x = pos.x *= TILE_SIZE;
	long start_y = pos.y *= TILE_SIZE - point_size / 2;
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

int get_map_item(int *map, int x, int y)
{
	if (x < 0 || x >= MAP_SIZE)
		return (1);
	if (y < 0 || y >= MAP_SIZE)
		return (1);
	return (map[y * MAP_SIZE + x]);
}

double	dda(t_vars *vars, t_vector *direction, double angle)
{
	t_vector step;
	t_vector intersect;
	t_player *player = &vars -> player;
	int *m = vars -> map.m;
	int color_red = adjust_transparancy(RED, 0);
	int color_blue = adjust_transparancy(BLUE, 0);
	int color;

	printf("player = (%f, %f)\n", player -> pos.x, player -> pos.y);
	intersect.y = floor(player -> pos.y) + 1 * (direction -> y > 0);
	intersect.x = (player -> pos.x + ((player -> pos.y - intersect.y) / tan(angle * (M_PI / 180))) );

	step.y = -1 + 2 * (direction -> y > 0);
	step.x = step.y / tan(-angle * (M_PI / 180));

	if (get_map_item(m, (int)floor(intersect.x), (int)floor(intersect.y)) == 1)
	{
		color = color_red;
		return 1;
	}
	else
		color = color_blue;
	draw_point(vars, intersect, 3, color);
	printf("direction.x = (%f, %f)\n", direction -> x, direction -> y);
	for(int i = 0; i < 20; i ++)
	{
		vect_add(&intersect, &step);
		if (get_map_item(m, (int)floor(intersect.x), (int)floor(intersect.y)))
		{
			return 1;
			color = color_red;
		}
		else
			color = color_blue;
		draw_point(vars, intersect, 3, color);
		printf("next intersection = (%f, %f)\n\n", intersect.x, intersect.y);
	}

	return (1);
}

void	draw_line(t_vars *vars, t_vector pos, t_vector *target_pos, int color)
{
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
