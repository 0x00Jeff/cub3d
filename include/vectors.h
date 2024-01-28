/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:26:00 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/28 20:45:10 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "../include/structs.h"

void	vect_assign(t_vector *to, t_vector *from);
void	vect_add(t_vector *to, t_vector *from);
void	vect_sub(t_vector *to, t_vector *from);
void	vect_scale(t_vector *to, float factor);
void	vect_div(t_vector *to, float divisor);
void	vect_normalize(t_vector *vect);
float	get_vect_len(t_vector *vect);
#endif
