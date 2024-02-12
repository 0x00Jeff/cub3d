/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:44:39 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 16:49:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

bool	is_player(int obj)
{
	return ((obj == SOUTH_IN_MAP) + (obj == NORTH_IN_MAP)
		+ (obj == WEST_IN_MAP) + (obj == EAST_IN_MAP));
}

void	register_player_pos(t_vars *vars, t_map *map)
{
	size_t	i;
	size_t	j;
	double	angle;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_player(map->m[i * map->width + j]))
			{
				angle = (map->m[i * map->width + j] - EAST_IN_MAP) * 90;
				vars->player.angle = angle;
				vars->player.pos = (t_vector){i + 0.5, j + 0.5};
				map->m[i * map->width + j] = 0;
				break ;
			}
			j++;
		}
		i++;
	}
}
