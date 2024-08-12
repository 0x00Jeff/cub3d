/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:54 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 16:17:42 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unused.h> // TODO : delete this later
#include <draw.h>
#include <structs.h>
#include <fps.h>

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

	ceil_color = adjust_transparancy(vars -> map.colors.ceiling, 1);
	floor_color = adjust_transparancy(vars -> map.colors.floor, 1);
	draw_rectangle(vars, (t_vector){0, 0}, (t_vector){M_WIDTH, M_HEIGHT >> 1},
		ceil_color);
	draw_rectangle(vars, (t_vector){0, M_HEIGHT >> 1}, (t_vector){M_WIDTH,
		M_HEIGHT}, floor_color);
}

void	do_graphics(t_vars *vars)
{
	static int		a;
	static double	old_time;

	(void)vars;
	if (a++ == 0)
	{
		draw_surroundings(vars);
		shoot_rays(vars, RAYS_NUM);
		draw_player(vars);
		draw_map(vars);
		draw_fps(vars);
	}
	if (mlx_get_time() - old_time > 0.016)
	{
		move_player(vars);
		old_time = mlx_get_time();
		if (!needs_clearing(vars))
		{
			draw_fps(vars);
			return ;
		}
		draw_surroundings(vars);
		shoot_rays(vars, RAYS_NUM);
		draw_player(vars); // TODO : delete this!!
		draw_map(vars);
		draw_fps(vars);
	}
}

void	dda(t_vars *vars, t_vector *direction, double angle, t_ray *ray)
{
	t_vector		h_step;
	t_vector		v_step;
	t_vector		h_intersect;
	t_vector		v_intersect;
 	const t_player	*player = &vars -> player;
	double			h_distance;
	double			v_distance;

	v_intersect.x = floor(player->pos.x) + (direction->x > 0);
	v_intersect.y = player->pos.y + (v_intersect.x - player->pos.x) * tan(-angle
			* (M_PI / 180));
	h_intersect.y = floor(player->pos.y) + (direction->y > 0);
	h_intersect.x = (player->pos.x + ((player->pos.y - h_intersect.y)
				/ tan(angle * (M_PI / 180))));
	h_step.y = -1 + 2 * (direction->y > 0);
	h_step.x = if_else(angle == 0, 1e69, h_step.y / tan(-angle * (M_PI / 180)));

	v_step.x = -1 + 2 * (direction->x > 0);
	v_step.y = tan(angle * (M_PI / 180));
	v_step.y *= if_else(direction->y < 0 && v_step.y > 0, -1, 1);
	v_step.y *= if_else(direction->y > 0 && v_step.y < 0, -1, 1);

	h_distance = calc_dist(vars, &h_intersect, (t_ivector){0, direction->y < 0}, &h_step);
	v_distance = calc_dist(vars, &v_intersect, (t_ivector){direction -> x < 0, 0}, &v_step);
	if (h_distance < v_distance)
	{
		set_intersection_point(ray, h_intersect, h_distance);
		ray->side = UP + 2 * (direction -> y > 0);
		ray->percent_in_tex = fabs(ray->to.x - floor(ray->to.x));
	}
	else
	{
		set_intersection_point(ray, v_intersect, v_distance);
		ray->side = RIGHT + 2 * (direction -> x < 0);
		ray->percent_in_tex = fabs(ray->to.y - floor(ray->to.y));
	}
	vect_scale(&ray->to, TILE_SIZE);
}
