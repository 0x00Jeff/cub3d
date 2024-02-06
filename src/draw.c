/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:54 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/06 20:54:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <draw.h>
#include <vectors.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utils.h>
#include <unused.h> // TODO : delete this later
#include <fps.h> // TODO : delete this later

void	move_player(t_vars *vars)
{
	void		*mlx;
	t_player	*player;

	mlx = vars->mlx;
	player = &vars->player;
	player->map_needs_clearing = player->pos.x * 10000 + \
		player->pos.y;
	player->old_angle = player->angle;
	if (mlx_is_key_down(mlx, MLX_KEY_K))
		player->fov += 3;
	if (mlx_is_key_down(mlx, MLX_KEY_J))
		player->fov -= 3;
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
	draw_rectangle(vars, (t_vector){0, 0}, (t_vector){M_WIDTH, M_HEIGHT / 2},
			adjust_transparancy(BLUE, 0.5));
	draw_rectangle(vars, (t_vector){0, M_HEIGHT / 2}, (t_vector){M_WIDTH,
			M_HEIGHT}, adjust_transparancy(BEIGE, 0.5));
}

void	do_graphics(t_vars *vars)
{
	static int		a;
	static double	old_time;

	(void)vars;
	if (a++ == 0)
	{
		//draw_surroundings(vars);
		//shoot_rays(vars, RAYS_NUM);
		//draw_player(vars);
		//draw_map(vars);
		//display_fps(vars);
	}
	if (mlx_get_time() - old_time > 0.016)
	{
		move_player(vars);
		old_time = mlx_get_time();
		if (!needs_clearing(vars))
		{
			display_fps(vars);
			return ;
		}
		draw_surroundings(vars);
		shoot_rays(vars, RAYS_NUM);
		draw_player(vars);
		draw_map(vars);
		//display_fps(vars);
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

void	draw_rectangle(t_vars *vars, t_vector start, t_vector end, int color)
{
	t_ivector	delta;

	delta.y = start.y;
	while (delta.y < end.y)
	{
		delta.x = start.x;
		while (delta.x < end.x)
			protected_mlx_put_pixel(vars->image, delta.x++, delta.y, color);
		delta.y++;
	}
}

void	draw_square(t_vars *vars, t_ivector pos, int tile_size, int color)
{
	t_ivector	delta;
	int			size;

	size = tile_size;
	delta.y = 0;
	while (delta.y < size)
	{
		delta.x = 0;
		while (delta.x < size)
		{
			protected_mlx_put_pixel(vars->image, pos.x * tile_size + delta.x,
					pos.y * tile_size + delta.y, color);
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

void	shoot_rays(t_vars *vars, int num)
{
	double		i;
	double		angle;
	t_vector	visual_player;
	t_ray		ray;
	int			color;

	color = adjust_transparancy(0xff0000, 0);
	color = adjust_transparancy(0x0000ff, 0);
	vect_assign(&visual_player, &vars->player.pos);
	vect_scale(&visual_player, TILE_SIZE);
	angle = vars->player.angle - (vars->player.fov >> 1);
	vect_assign(&ray.from, &visual_player);
	i = 0;
	while (i < num)
	{
		vect_assign(&ray.to, &visual_player);
		shoot_ray(vars, &ray, angle);
		draw_stripe(vars, &ray, i, angle);
		angle += (double)vars->player.fov / num;
		i++;
	}
}

void	shoot_ray(t_vars *vars, t_ray *ray, double angle)
{
	t_vector	direction;
	t_vector	tmp_from;
	t_vector	tmp_to;

	inc_pos_vect(&ray->to, 1, angle);
	vect_sub(&ray->to, &ray->from);
	vect_assign(&direction, &ray->to);
	vect_add(&ray->to, &ray->from);
	dda(vars, &direction, -angle, ray);
	vect_assign(&tmp_from, &ray->from);
	vect_assign(&tmp_to, &ray->to);
	vect_scale(&tmp_from, MAP_SCALE_FACTOR);
	vect_scale(&tmp_to, MAP_SCALE_FACTOR);
	SKIP
	draw_line(vars, tmp_from, &tmp_to, adjust_transparancy(GREEN, 0));

}

void	draw_stripe(t_vars *vars, t_ray *ray, int x, double angle)
{
	t_ivector	wall_start;
	t_ivector	wall_end;
	int			start_y;
	int			end_y;
	double		wall_len;
	int			color;

	wall_len = M_HEIGHT / (ray->distance * (cos((vars->player.angle - angle)
					* (M_PI / 180))) * sin((vars->player.fov / 2) * (M_PI / 180)));
	wall_start.y = M_HEIGHT / 2 - wall_len / 2;
	wall_end.y = M_HEIGHT / 2 + wall_len / 2;
	start_y = wall_start.y;
	end_y = wall_end.y;
	if (wall_start.y < 0)
		start_y = 0;
	if (wall_end.y >= M_HEIGHT)
		end_y = M_HEIGHT - 1;
	color = adjust_transparancy(GREEN, 0.7);
	mlx_texture_t *tex;
	tex = vars -> texture[ray -> side];

	int x_tex = ray -> percent_in_tex * tex -> width;
	int i = start_y;
	while(i < end_y)
	{
		int y_tex = tex -> height * (double)(i - wall_start.y) / (wall_end.y - wall_start.y);
		uint32_t pix = ((uint32_t *)tex -> pixels)[y_tex * tex -> width + x_tex];
		protected_mlx_put_pixel(vars -> image, x, i++, swap_endianess(pix));
	}
}

void	dda(t_vars *vars, t_vector *direction, double angle, t_ray *ray)
{
	t_vector	h_step;
	t_vector	v_step;
	t_vector	h_intersect;
	t_vector	v_intersect;
	t_player	*player;
	float		h_distance;
	float		v_distance;

	player = &vars->player;
	v_intersect.x = floor(player->pos.x) + 1 * (direction->x > 0);
	v_intersect.y = player->pos.y + (v_intersect.x - player->pos.x) * tan(-angle
			* (M_PI / 180));
	h_intersect.y = floor(player->pos.y) + 1 * (direction->y > 0);
	h_intersect.x = (player->pos.x + ((player->pos.y - h_intersect.y)
				/ tan(angle * (M_PI / 180))));
	h_step.y = -1 + 2 * (direction->y > 0);
	h_step.x = (angle == 0) ? 1e69 : h_step.y / tan(-angle * (M_PI / 180));
	v_step.x = -1 + 2 * (direction->x > 0);
	v_step.y = tan(angle * (M_PI / 180));
	v_step.y *= (direction->y < 0 && v_step.y > 0) ? -1 : 1;
	v_step.y *= (direction->y > 0 && v_step.y < 0) ? -1 : 1;
	for (int i = 0; i < 2000; i++)
	{
		if (get_map_item(&vars->map, h_intersect.x, h_intersect.y
				- (direction->y < 0)))
			break ;
		vect_add(&h_intersect, &h_step);
	}
	for (int i = 0; i < 2000; i++)
	{
		if (get_map_item(&vars->map, v_intersect.x - (direction->x < 0),
				v_intersect.y))
			break ;
		vect_add(&v_intersect, &v_step);
	}
	h_distance = vect_get_distance(&player->pos, &h_intersect);
	v_distance = vect_get_distance(&player->pos, &v_intersect);
	if (h_distance < v_distance)
	{
		ray->to = h_intersect;
		ray->distance = h_distance;
		if (direction->y > 0)
			ray->side = DOWN;
		else
			ray->side = UP;
		ray -> percent_in_tex = fabs(ray -> to.x - floor(ray -> to.x));
	}
	else
	{
		ray->to = v_intersect;
		ray->distance = v_distance;
		if (direction->x > 0)
			ray->side = RIGHT;
		else
			ray->side = LEFT;
		ray -> percent_in_tex = fabs(ray -> to.y - floor(ray -> to.y));
	}
	vect_scale(&ray->to, TILE_SIZE);
}
