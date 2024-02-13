/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:06:34 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 22:56:54 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <draw.h>

void	init_intersections(t_vars *vars, t_intersection *inter,
			t_vector *direction, double angle)
{
	const t_player	*player = &vars -> player;

	inter -> v.x = floor(player->pos.x) + (direction->x > 0);
	inter -> v.y = player->pos.y + (inter -> v.x - player->pos.x) * tan(-angle
			* (M_PI / 180));
	inter -> h.y = floor(player->pos.y) + (direction->y > 0);
	inter -> h.x = (player->pos.x + ((player->pos.y - inter -> h.y)
				/ tan(angle * (M_PI / 180))));
	inter -> v_dist = 0;
	inter -> h_dist = 0;
}

void	init_steps(t_vars *vars, t_intersection *inter,
		t_vector *direction, double angle)
{
	inter -> h_step.y = -1 + 2 * (direction->y > 0);
	inter -> h_step.x = if_else(angle == 0, 1e69,
			inter -> h_step.y / tan(-angle * (M_PI / 180)));
	inter -> v_step.x = -1 + 2 * (direction->x > 0);
	inter -> v_step.y = tan(angle * (M_PI / 180));
	inter -> v_step.y *= if_else(direction->y < 0
			&& inter -> v_step.y > 0, -1, 1);
	inter -> v_step.y *= if_else(direction->y > 0
			&& inter -> v_step.y < 0, -1, 1);
	inter -> h_dist = calc_dist(vars, &inter -> h,
			(t_ivector){0, direction->y < 0}, &inter -> h_step);
	inter -> v_dist = calc_dist(vars, &inter -> v,
			(t_ivector){direction -> x < 0, 0}, &inter -> v_step);
}

void	dda(t_vars *vars, t_vector *direction, double angle, t_ray *ray)
{
	t_intersection	inter;

	init_intersections(vars, &inter, direction, angle);
	init_steps(vars, &inter, direction, angle);
	if (inter.h_dist < inter.v_dist)
	{
		set_intersection_point(ray, inter.h, inter.h_dist);
		ray->side = UP + 2 * (direction -> y > 0);
		ray->percent_in_tex = fabs(ray->to.x - floor(ray->to.x));
	}
	else
	{
		set_intersection_point(ray, inter.v, inter.v_dist);
		ray->side = RIGHT + 2 * (direction -> x < 0);
		ray->percent_in_tex = fabs(ray->to.y - floor(ray->to.y));
	}
	vect_scale(&ray->to, TILE_SIZE);
}
