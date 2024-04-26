/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:25:52 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 16:53:56 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vectors.h>
#include <math.h>

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

float	vect_get_distance(t_vector *p1, t_vector *p2)
{
	t_vector	tmp;

	vect_assign(&tmp, p1);
	vect_sub(&tmp, p2);
	return (get_vect_len(&tmp));
}

void	vect_addi(t_vector *to, int n)
{
	to->x += n;
	to->y += n;
}
