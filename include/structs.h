/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:45:04 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/24 21:17:13 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../mlx/include/MLX42/MLX42.h"
# include <dlfcn.h>

# define M_WIDTH 1920
# define M_HEIGHT 1080
# define DICK_SIZE 2

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_ivector
{
	int			x;
	int			y;
}				t_ivector;

typedef struct s_player
{
	t_vector	pos;
	float		angle;
	double		map_needs_clearing;
	int			mouse_needs_clearing;
}				t_player;

typedef struct s_vars
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	player;
	t_ivector	mouse;
}				t_vars;
#endif
