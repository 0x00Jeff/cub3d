/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:45:04 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/05 18:14:35 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../mlx/include/MLX42/MLX42.h"
# include <dlfcn.h>

# define M_WIDTH 1920
# define M_HEIGHT 1080
# define PLAYER_SIZE 5
# define MAP_SIZE 15

# define PRIV_ESC 0xffffffff
# define NIGGER 0
# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff
# define BEIGE 0xF5F5DC

enum
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NORTH = UP,
	EAST = RIGHT,
	SOUTH = DOWN,
	WEST = LEFT
};

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

typedef struct s_ray
{
	t_vector		from;
	t_vector		to;
	t_vector		direction;
	float			distance;
	int				side;
	double			angle;
	double			percent_in_tex;
}					t_ray;

typedef struct s_player
{
	t_vector		pos;
	float			angle;
	double			map_needs_clearing;
	float			old_angle;
	int				fov;
}					t_player;

typedef struct s_map
{
	int				height;
	int				width;
	int				*m;
	int				color;
}					t_map;

typedef struct s_vars
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_player		player;
	t_ivector		mouse;
	t_map			map;
	mlx_texture_t	*texture[4];
}					t_vars;
#endif
