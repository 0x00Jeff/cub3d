/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:41 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/08 15:54:45 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H
# include "../include/structs.h"
# include "../mlx/include/MLX42/MLX42.h"

typedef void	(*t_do_graphics)(t_vars *vars);
t_do_graphics	g_do_graphics_ptr = NULL;
void			*g_module = NULL;

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};
void	init_player_data(t_vars *vars);
void			install_hooks(t_vars *vars);
void			win_close(void *param);
void			print_key(void *param);
#endif
