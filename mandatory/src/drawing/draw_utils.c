/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:30:49 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 14:01:22 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <draw.h>
#include <utils.h>
#include <vectors.h>

void	set_intersection_point(t_ray *ray, t_vector intersect, double dist)
{
	ray -> to = intersect;
	ray -> distance = dist;
}

double	calc_dist(t_vars *vars, t_vector *intersect, t_ivector condition,
		t_vector *step)
{
	t_map	*map;
	int		i;

	i = 0;
	map = &vars->map;
	while (i < 500)
	{
		if (get_map_item(map, intersect->x - condition.x, intersect->y
				- condition.y))
			break ;
		vect_add(intersect, step);
		i++;
	}
	if (i >= 500)
		return (2000);
	return (vect_get_distance(&vars->player.pos, intersect));
}

double	if_else(bool condition, double _true, double _false)
{
	if (condition)
		return (_true);
	return (_false);
}

void	protected_mlx_put_pixel(mlx_image_t *image, int x, int y, int color)
{
	if ((x < 0) | (x >= M_WIDTH) | (y < 0) | (y >= M_HEIGHT))
		return ;
	mlx_put_pixel(image, x, y, color);
}
