/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:48 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/05 15:56:56 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vectors.h>

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
