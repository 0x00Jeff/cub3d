/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:01:26 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 00:03:25 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H
# include <parse.h>
# include <structs.h>

enum
{
	BLANK,
	WALL,
};

int		validator(t_vars *vars);
size_t	count_object(t_map *map, int object);
size_t	count_players(t_map *map);
int		check_for_invalid_characters(t_map *map);
#endif
