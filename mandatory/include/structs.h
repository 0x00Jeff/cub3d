/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:45:04 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 22:55:55 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../mlx/include/MLX42/MLX42.h"
# include <dlfcn.h>
# include <fcntl.h>
# include <stdio.h>
# include <vectors.h>

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
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	NORTH = UP,
	EAST = RIGHT,
	SOUTH = DOWN,
	WEST = LEFT,
};

typedef struct s_intersection
{
	t_vector		h;
	t_vector		v;
	t_vector		v_step;
	t_vector		h_step;
	double			h_dist;
	double			v_dist;
}					t_intersection;

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

typedef struct s_surroundings
{
	int				ceiling;
	int				floor;
	int				ceiling_set;
	int				floor_set;
}					t_surroundings;

typedef struct s_map
{
	int				fd;
	size_t			height;
	size_t			width;
	int				*data;
	char			*tex[4];
	t_surroundings	colors;
}					t_map;

typedef struct e_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}					t_color;

typedef struct s_vars
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_player		player;
	t_ivector		mouse;
	t_map			map;
	mlx_texture_t	*texture[4];
}					t_vars;

typedef struct s_lil_end
{
	char			c1;
	char			c2;
	char			c3;
	char			c4;
}					t_lil_end;

#endif
