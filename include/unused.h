/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:12:14 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/07 15:08:09 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNUSED_H
# define UNUSED_H
# include <draw.h>
# include <math.h>
# include <stdlib.h>
# include <vectors.h>
# include <utils.h>
# include <draw.h>
# define SKIP ;

void	draw_point(t_vars *vars, t_vector pos, int point_size, int color);
void	draw_player(t_vars *vars);
void	draw_point2(t_vars *vars, int x, int y, int point_size, int color);
void	draw_line(t_vars *vars, t_vector pos, t_vector *target_pos, int color);
void	draw_map(t_vars *vars);
void	clear_screen(t_vars *vars);
#endif
