/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:39:54 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/26 14:22:44 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/vectors.h"
#include <math.h>
#include <stdio.h> // to delete
#include <stdlib.h>
#include <time.h>

int	adjust_transparancy(int color, float trans)
{
	if (trans < 0)
		trans = -trans;
	if (trans > 1)
		trans = 1;
	return ((color << 8) + (int)(0xff - (trans * 0xff)));
}

void	draw_player(t_vars *vars)
{
	int	size;
	int	start_x;
	int	start_y;

	start_x = (int)vars->player.pos.x;
	start_y = (int)vars->player.pos.y - DICK_SIZE;
	for (size = 0; size <= DICK_SIZE; size++)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars->image, start_x + j, start_y,
					0xffffffff);
		start_y++;
	}
	for (; size >= 0; size--)
	{
		for (int j = -size; j <= size; j++)
			protected_mlx_put_pixel(vars->image, start_x + j, start_y,
					0xffffffff);
		start_y++;
	}
}

void	inc_pos_vect(t_vector *vect, double angle)
{
	vect->x += SPEED * cos(angle * (M_PI / 180));
	vect->y += SPEED * sin(angle * (M_PI / 180));
}

void	move_player(t_vars *vars)
{
	void		*mlx;
	t_player	*player;

	mlx = vars->mlx;
	player = &vars->player;
	player->map_needs_clearing = player->pos.x * 10000 +
		player->pos.y;
	player->old_angle = player->angle;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->angle += ROT_SPEED;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->angle -= ROT_SPEED;

	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		player->pos.x -= SPEED * cos((player->angle - 90) * (M_PI / 180));
		player->pos.y -= SPEED * sin((player->angle - 90) * (M_PI / 180));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		player->pos.x -= SPEED * cos((player->angle + 90) * (M_PI / 180));
		player->pos.y -= SPEED * sin((player->angle + 90) * (M_PI / 180));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
	{
		player->pos.x -= SPEED * cos(player->angle * (M_PI / 180));
		player->pos.y -= SPEED * sin(player->angle * (M_PI / 180));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
	{
		player->pos.x += SPEED * cos(player->angle * (M_PI / 180));
		player->pos.y += SPEED * sin(player->angle * (M_PI / 180));
	}

	return ;
}

/*
void	register_mouse_pos(t_vars *vars)
{
	t_ivector	mouse;

	mlx_get_mouse_pos(vars->mlx, &mouse.x, &mouse.y);
	vars->player.mouse_needs_clearing = mouse.x * 10000 + mouse.y;
}
*/

int	needs_clearing(t_vars *vars)
{
	t_player	*player;

	//	t_ivector	mouse;
	player = &vars->player;
	if (player->map_needs_clearing != player->pos.x * 10000 + player->pos.y)
		return (1);
	//	mlx_get_mouse_pos(vars->mlx, &mouse.x, &mouse.y);
	//	if (player->mouse_needs_clearing != (mouse.x * 10000 + mouse.y))
	//		return (1);
	if (player->angle != player->old_angle)
	{
		player->old_angle = player->angle;
		return (1);
	}
	return (0);
}

void	do_graphics(void *param)
{
	t_vars	*vars;

	static int dead = 0;
	static int total = 0;
	static int rays_number = 270;
	vars = param;
	move_player(vars);
	t_player old_player = ((t_vars *)param) -> player;
//	if (!needs_clearing(vars))
//		return ;
	clear_screen(param);
	draw_player(vars);

	shoot_rays(param, rays_number, 250);
	if ((total / 20) % 2)
		rays_number = 360;
	else
		rays_number = 270;
	total++;

	static t_player p =
	{
		.pos = {
			.x = 900,
			.y = 600
		},
		.angle = 0,
	};
	(void)p;
	((t_vars *)param) -> player2 = p;
	printf("distance = %f\n", vect_get_distance(&p.pos, &old_player.pos));
	float d = vect_get_distance(&p.pos, &old_player.pos);
	if (d < 350 && d > 250)
		rays_number = 270;
	if (vect_get_distance(&p.pos, &old_player.pos) < 250 && (total / 20) % 2)
		dead = 1;
	if (!dead)
		shoot_rays(param, 380, 25);
	if (dead)
	{
		do
		{
			srand(time(NULL));
			p.pos.x = rand() % 1920;
			p.pos.y = rand() % 1080;
		}while(vect_get_distance(&p.pos, &old_player.pos) < 250);
		dead = 0;
	}

	((t_vars *)param) -> player = old_player;

	//register_mouse_pos(vars);
	return;
}

void	clear_screen(t_vars *vars)
{
	int	adjusted_color;

	;
	adjusted_color = adjust_transparancy(0xffffff, 0.5);
	for (int i = 0; i < (1920 / 69) + 1; i++)
	{
		for (int j = 0; j < (1080 / 69) + 1; j++)
			draw_square(vars, (t_ivector){i * 69, j * 69}, 69, ((i + j)
						% 2) ? adjusted_color : 0);
	}
}

void	draw_square(t_vars *vars, t_ivector pos, int size, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			protected_mlx_put_pixel(vars->image, pos.x + dx, pos.y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	protected_mlx_put_pixel(mlx_image_t *image, int x, int y, int color)
{
	if ((x < 0) | (x >= M_WIDTH) | (y < 0) | (y >= M_HEIGHT))
		return ;
	mlx_put_pixel(image, x, y, color);
}

void	shoot_rays(t_vars *vars, int num, int factor)
{
	double		i;
	int			color;
	double		angle;
	t_vector	target;

	color = adjust_transparancy(0xff0000, 0);
	if (num == 380)
		color = adjust_transparancy(0x00ff00, 0);
	i = -num / 2;
	angle = vars->player.angle + 180;
	while (i < ((num / 2) + (num % 2)))
	{
	if (num == 380)
	{
		target.x = vars->player2.pos.x;
		target.y = vars->player2.pos.y;
		target.x += factor * cos((angle + i) * (M_PI / 180));
		target.y += factor * sin((angle + i) * (M_PI / 180));
		draw_line(vars, vars->player2.pos, &target, color);
		i += 0.5;
	}
	else
	{
		target.x = vars->player.pos.x;
		target.y = vars->player.pos.y;
		target.x += factor * cos((angle + i) * (M_PI / 180));
		target.y += factor * sin((angle + i) * (M_PI / 180));
		draw_line(vars, vars->player.pos, &target, color);
		i += 0.5;
	}
	}
}

void	draw_line(t_vars *vars, t_vector pos, t_vector *target_pos, int color)
{
	t_vector	delta;
	t_vector	inc;
	double		step;
	int			i;

	i = 0;
	delta.x = target_pos->x - pos.x;
	delta.y = target_pos->y - pos.y;
	if (abs((int)delta.x) > abs((int)delta.y))
		step = delta.x;
	else
		step = delta.y;
	if (step < 0)
		step *= -1;
	inc.x = delta.x / step;
	inc.y = delta.y / step;
	while (i < step)
	{
		protected_mlx_put_pixel(vars->image, roundf(pos.x), roundf(pos.y),
				color);
		vect_add(&pos, &inc);
		i++;
	}
}
