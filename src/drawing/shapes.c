/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:55:16 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 15:51:41 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <draw.h>
#include <vectors.h>

void	draw_square(t_vars *vars, t_ivector pos, int tile_size, int color)
{
	t_vector	start;
	t_vector	end;

	start.x = pos.x;
	start.y = pos.y;
	vect_scale(&start, tile_size);
	vect_assign(&end, &start);
	vect_addi(&end, tile_size);
	draw_rectangle(vars, start, end, color);
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

void static	init_wall(t_wall *wall)
{
	wall->draw_start.y = M_HEIGHT / 2 - wall->len / 2;
	wall->draw_end.y = M_HEIGHT / 2 + wall->len / 2;
	wall->start_y = wall->draw_start.y;
	wall->end_y = wall->draw_end.y;
	if (wall->draw_start.y < 0)
		wall->start_y = 0;
	if (wall->draw_end.y >= M_HEIGHT)
		wall->end_y = M_HEIGHT - 1;
}

void	draw_stripe(t_vars *vars, t_ray *ray, int x, double angle)
{
	t_wall			wall;
	mlx_texture_t	*tex;
	t_ivector		itex;
	int				i;
	uint32_t		pix;

	wall.len = M_HEIGHT / (ray->distance * (cos((vars->player.angle - angle)
					* (M_PI / 180))) * sin((vars->player.fov / 2) * (M_PI
					/ 180)));
	init_wall(&wall);
	tex = vars->texture[ray->side];
	itex.x = ray->percent_in_tex * tex->width;
	i = wall.start_y;
	while (i < wall.end_y)
	{
		itex.y = tex->height * (double)(i - wall.draw_start.y)
			/ (wall.draw_end.y - wall.draw_start.y);
		pix = ((uint32_t *)tex->pixels)[itex.y * tex->width + itex.x];
		protected_mlx_put_pixel(vars->image, x, i++, swap_endianess(pix));
	}
}
