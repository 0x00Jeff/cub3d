/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:25:52 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/28 20:44:21 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vectors.h"
#include <math.h>

void	vect_assign(t_vector *to, t_vector *from)
{
	to->x = from->x;
	to->y = from->y;
}

void	vect_add(t_vector *to, t_vector *from)
{
	to->x += from->x;
	to->y += from->y;
}

void	vect_sub(t_vector *to, t_vector *from)
{
	to->x -= from->x;
	to->y -= from->y;
}

void	vect_scale(t_vector *to, float factor)
{
	to->x *= factor;
	to->y *= factor;
}

void	vect_div(t_vector *to, float divisor)
{
	if (divisor == 0)
		return ;
	to->x /= divisor;
	to->y /= divisor;
}

void	vect_normalize(t_vector *vect)
{
	float	len;

	len = get_vect_len(vect);
	vect_div(vect, len);
}

float	get_vect_len(t_vector *vect)
{
	return (sqrt((vect->x * vect->x) + (vect->y * vect->y)));
}
