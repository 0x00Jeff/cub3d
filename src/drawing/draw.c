/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:54 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 12:29:10 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <draw.h>
#include <structs.h>

void	rotate_player(t_vars *vars)
{
	void		*mlx;
	t_player	*player;

	mlx = vars->mlx;
	player = &vars->player;
	if (mlx_is_key_down(mlx, MLX_KEY_K))
		player->fov += 3;
	if (mlx_is_key_down(mlx, MLX_KEY_J))
		player->fov -= 3;
}

void	move_player(t_vars *vars)
{
	void		*mlx;
	t_player	*player;
	double		speed;

	speed = (double)SPEED / (double)TILE_SIZE;
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
		inc_pos_vect(&player->pos, -speed, player->angle - 90);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		inc_pos_vect(&player->pos, -speed, player->angle + 90);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		inc_pos_vect(&player->pos, -speed, player->angle);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
		inc_pos_vect(&player->pos, speed, player->angle);
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

void	draw_surroundings(t_vars *vars)
{
	int	ceil_color;
	int	floor_color;

	ceil_color = adjust_transparancy(vars -> map.colors.ceiling, 0.5);
	floor_color = adjust_transparancy(vars -> map.colors.floor, 0.5);
	draw_rectangle(vars, (t_vector){0, 0}, (t_vector){M_WIDTH, M_HEIGHT / 2},
		ceil_color);
	draw_rectangle(vars, (t_vector){0, M_HEIGHT / 2}, (t_vector){M_WIDTH,
		M_HEIGHT}, floor_color);
}

void	do_graphics(t_vars *vars)
{
	static int		a;
	static double	old_time;

	if (a++ == 0)
	{
		draw_surroundings(vars);
		shoot_rays(vars, RAYS_NUM);
		draw_fps(vars);
	}
	if (mlx_get_time() - old_time > 0.016)
	{
		move_player(vars);
		old_time = mlx_get_time();
		if (!needs_clearing(vars))
			return ;
		draw_surroundings(vars);
		shoot_rays(vars, RAYS_NUM);
		draw_fps(vars);
	}
}
