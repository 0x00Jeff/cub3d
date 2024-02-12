/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:34:55 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 15:40:46 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <draw.h>
#include <unused.h> //  TODO : delete later

void	shoot_rays(t_vars *vars, int num)
{
	double		i;
	double		angle;
	t_vector	visual_player;
	t_ray		ray;

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
	SKIP;
	//draw_line(vars, tmp_from, &tmp_to, adjust_transparancy(RED, 0));
}
