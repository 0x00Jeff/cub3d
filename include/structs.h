/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:45:04 by afatimi           #+#    #+#             */
/*   Updated: 2024/01/23 19:49:20 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../mlx/include/MLX42/MLX42.h"
# include <dlfcn.h>

#define M_WIDTH		1920
#define M_HEIGHT	1080
#define DICK_SIZE	2

typedef struct s_vars
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}			t_vars;
#endif
