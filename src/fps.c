/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:39:43 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/06 20:49:44 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fps.h>

static void	draw_digit(t_vars *vars, int digit, t_ivector pos, int size)
{
	t_ivector iter;
	t_ivector tmp;
	static int	digits_patt[5][3 * 10] = {
	{1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1,
		0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
	{1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}};

	iter = (t_ivector){0, 0};
	while (iter.y < 5)
	{
		while (iter.x < 3)
		{
			if (digits_patt[iter.y][iter.x + (digit % 10) * 3])
			{
				tmp.x = (int)(pos.x + iter.x * size);
				tmp.y = (int)pos.y + iter.y * size;
				draw_square(vars, tmp, size, 0xFF6942FF);
			}
			++iter.x;
		}
		iter = (t_ivector){0, iter.y + 1};
	}
}

static void	draw_number(t_vars *vars, int number, t_ivector pos, int size)
{
	int	i;

	draw_digit(vars, number % 10,
		(t_ivector){pos.x - 3 * size - size, pos.y}, size);
	number /= 10;
	i = 2;
	while (number > 0)
	{
		draw_digit(vars, number % 10,
			(t_ivector){pos.x - (3 * size + size / 2) * i - size, pos.y}, size);
		number /= 10;
		++i;
	}
}

void	draw_fps(t_vars *vars)
{
	static double	old_time = 0;
	static int		fps;
	double			current_time;

	current_time = mlx_get_time();
	if (current_time - old_time > 0.2)
	{
		fps = 1 / vars->mlx->delta_time;
		printf("fps: %d    \r", fps);
		fflush(stdout);
		old_time = current_time;
	}
	draw_number(vars, fps, (t_ivector){vars->mlx->width, 10}, 10);
}
