/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:32:59 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 17:50:27 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "../mlx/include/MLX42/MLX42.h"
# include <math.h>
# include <structs.h>
# include <utils.h>
# include <vectors.h>
# define ROT_SPEED 4
# define TILE_SIZE 64
# define SPEED ((double)5 / (double)TILE_SIZE)
# define RAY_LEN 10
# define RAYS_NUM 1920
# define MAP_SCALE_FACTOR 0.5

typedef struct e_wall
{
	t_ivector	draw_start;
	t_ivector	draw_end;
	int			start_y;
	int			end_y;
	double		len;
}				t_wall;

double			if_else(bool condition, double _true, double _false);
void			set_intersection_point(t_ray *ray, t_vector intersect,
					double dist);
double			calc_dist(t_vars *vars, t_vector *intersect,
					t_ivector condition, t_vector *step);
void			rotate_player(t_vars *vars);
void			draw_rectangle(t_vars *vars, t_vector start, t_vector end,
					int color);
void			clear_screen(t_vars *vars);
void			draw_square(t_vars *vars, t_ivector pos, int tile_size,
					int color);
void			protected_mlx_put_pixel(mlx_image_t *image, int x, int y,
					int color);
void			draw_line(t_vars *vars, t_vector pos, t_vector *target_pos,
					int color);
void			shoot_ray(t_vars *vars, t_ray *ray, double angle);
void			shoot_rays(t_vars *vars, int num);
void			move_player(t_vars *vars);
void			draw_map(t_vars *vars);
void			dda(t_vars *vars, t_vector *direction, double angle,
					t_ray *ray);
void			draw_stripe(t_vars *vars, t_ray *ray, int x, double angle);
void			draw_surroundings(t_vars *vars);
#endif
