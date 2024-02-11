/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:26:00 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 17:29:15 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_ivector
{
	int				x;
	int				y;
}					t_ivector;

void	vect_assign(t_vector *to, t_vector *from);
void	vect_add(t_vector *to, t_vector *from);
void	vect_sub(t_vector *to, t_vector *from);
void	vect_scale(t_vector *to, float factor);
void	vect_div(t_vector *to, float divisor);
void	vect_normalize(t_vector *vect);
float	get_vect_len(t_vector *vect);
float	vect_get_distance(t_vector *p1, t_vector *p2);
void	vect_addi(t_vector *to, int n);
#endif
