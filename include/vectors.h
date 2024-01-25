/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:26:00 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/25 16:37:39 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "../include/structs.h"

void	vect_assign(t_vector *to, t_vector *from);
void	vect_add(t_vector *to, t_vector *from);
void	vect_sub(t_vector *to, t_vector *from);
void	vect_mul(t_vector *to, float factor);
void	vect_div(t_vector *to, float divisor);
void	vect_normalize(t_vector *vect);
float	get_vect_len(t_vector *vect);
float	vect_get_distance(t_vector *vect1, t_vector *vect2);
#endif
