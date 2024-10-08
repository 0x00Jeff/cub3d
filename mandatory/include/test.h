/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:17:33 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/09 12:13:24 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "../include/structs.h"
# include "../mlx/include/MLX42/MLX42.h"
# include <dlfcn.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void		install_hooks(t_vars *vars);
int			init_player_data(t_vars *vars);
#endif
