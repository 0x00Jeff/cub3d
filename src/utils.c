/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:13:28 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/06 20:02:33 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <fps.h>

uint32_t	swap_endianess(uint32_t value)
{
	t_lil_end	l1;
	t_lil_end	l2;

	l1 = *(t_lil_end *)&value;
	l2.c4 = l1.c1;
	l2.c3 = l1.c2;
	l2.c2 = l1.c3;
	l2.c1 = l1.c4;
	return (*(uint32_t *)&l2);
}

int	adjust_transparancy(int color, float trans)
{
	if (trans < 0)
		trans = -trans;
	if (trans > 1)
		trans = 1;
	return ((color << 8) + (int)(0xff - (trans * 0xff)));
}

void	inc_pos_vect(t_vector *vect, double factor, double angle)
{
	vect->x += factor * cos(angle * (M_PI / 180));
	vect->y += factor * sin(angle * (M_PI / 180));
}

// TODO : draw the fps on the screen instead!
void	display_fps(t_vars *vars)
{
	//draw_fps(vars);
	return;
	static double	old_time;
	int				fps;

	fps = (int)(1 / vars->mlx->delta_time);
	if (mlx_get_time() - old_time > 0.25)
	{
		printf("fps: %d    \r", fps);
		fflush(stdout);
		old_time = mlx_get_time();
	}
}

int	get_map_item(t_map *map, double _x, double _y)
{
	int	x;
	int	y;
	int	*m;

	m = map->m;
	x = (int)floor(_x);
	y = (int)floor(_y);
	if (x < 0 || x >= map->width)
		return (0);
	if (y < 0 || y >= map->height)
		return (0);
	return (m[y * map->width + x]);
}
