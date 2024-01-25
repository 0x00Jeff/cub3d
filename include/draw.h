/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:38:22 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/25 18:33:18 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "../include/structs.h"
# include "../mlx/include/MLX42/MLX42.h"
# define ROT_SPEED	6
# define SPEED		9



void	draw_player(t_vars *vars);
void	clear_screen(t_vars *vars);
void	draw_square(t_vars *vars, t_ivector pos, int size, int color);
void	protected_mlx_put_pixel(mlx_image_t *image, int x, int y, int color);
void	draw_line(t_vars *vars, t_vector pos, t_vector *target_pos, int color);
void	shoot_rays(t_vars *vars, int num, int factor);
void	move_player(t_vars *vars);
#endif
