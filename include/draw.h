/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:38:22 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/21 19:01:20 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "../include/structs.h"
# include "../mlx/include/MLX42/MLX42.h"

void	draw_player(t_vars *vars, int start_x, int start_y);
void	clear_screen(t_vars *vars);
void	draw_square(t_vars *vars, int x, int y, int size, int color);
void	protected_mlx_put_pixel(mlx_image_t *image, int x, int y, int color);
#endif
