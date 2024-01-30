/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:32:59 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/30 18:02:37 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "../include/structs.h"
# include "../mlx/include/MLX42/MLX42.h"
# define ROT_SPEED 4
# define SPEED ((double)10 / (double)69)
# define RAY_LEN 250
# define RAYS_NUM 420 - 69 * 2
# define TILE_SIZE 69

void	draw_player(t_vars *vars);
void	clear_screen(t_vars *vars);
void	draw_square(t_vars *vars, t_ivector pos, int color);
void	protected_mlx_put_pixel(mlx_image_t *image, int x, int y, int color);
void	draw_line(t_vars *vars, t_vector pos, t_vector *target_pos, int color);
void	shoot_rays(t_vars *vars, int num, int factor);
void	move_player(t_vars *vars);
void	inc_pos_vect(t_vector *vect, double factor, double angle);
void	draw_map(t_vars *vars);
void	display_fps(t_vars *vars);
void	dda(t_vars *vars, t_vector *vect, double angle, t_vector *collision);
#endif
