/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:02:36 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/06 17:17:18 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <math.h>
# include <stdio.h>
# include <structs.h>
# include <unistd.h>

uint32_t	swap_endianess(uint32_t value);
int			adjust_transparancy(int color, float trans);
void		inc_pos_vect(t_vector *vect, double factor, double angle);
void		display_fps(t_vars *vars);
int			get_map_item(t_map *map, double _x, double _y);
#endif
