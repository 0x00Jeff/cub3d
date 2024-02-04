/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:32:59 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/04 16:33:16 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "../include/structs.h"
# include "../mlx/include/MLX42/MLX42.h"
# define ROT_SPEED 4
# define TILE_SIZE 64
# define SPEED ((double)10 / (double)TILE_SIZE)
# define RAY_LEN 10
# define RAYS_NUM 1920
# define MAP_SCALE_FACTOR	0.25

void	draw_player(t_vars *vars);
void	draw_point(t_vars *vars, t_vector pos, int point_size, int color);
void	draw_point2(t_vars *vars, int x, int y, int point_size, int color);
//  DEBUG
void	draw_rectangle(t_vars *vars, t_vector start, t_vector end, int color);
void	clear_screen(t_vars *vars);
void	draw_square(t_vars *vars, t_ivector pos, int tile_size, int color);
void	protected_mlx_put_pixel(mlx_image_t *image, int x, int y, int color);
void	draw_line(t_vars *vars, t_vector pos, t_vector *target_pos, int color);
void	shoot_ray(t_vars *vars, t_ray *ray, double angle, int color);
void	shoot_rays(t_vars *vars, int num);
void	move_player(t_vars *vars);
void	inc_pos_vect(t_vector *vect, double factor, double angle);
void	draw_map(t_vars *vars);
void	display_fps(t_vars *vars);
void	dda(t_vars *vars, t_vector *direction, double angle, t_ray *ray);
void	draw_stripe(t_vars *vars, t_ray *ray, int x, double angle);
void	shoot_ray(t_vars *vars, t_ray *ray, double angle, int color);
int		get_map_item(t_map *map, double _x, double _y);
void	draw_surroundings(t_vars *vars);
#endif
