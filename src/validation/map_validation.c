/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:01:27 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/10 21:36:14 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<validation.h>
#include<stdio.h>

int validator(t_vars *vars)
{
	t_map *map = &vars->map;

	if (!check_for_invalid_characters(map))
		return (ft_putstr_fd("Error\nfound weird chars in map!\n",
				2), 1);
	// one player -> done
	if (count_players(map) != 1)
		return (ft_putstr_fd("Error\nThere has to be one player on the map\n",
				2), 1);
	// closed map
	// weird characters

	(void)map;
	return (0);
}
