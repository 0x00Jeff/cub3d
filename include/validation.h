/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:01:26 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 13:50:33 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H
# include <parse.h>
# include <structs.h>
# define ll long long

enum
{
	BLANK,
	WALL,
};

int		validator(t_vars *vars);
size_t	count_object(t_map *map, int object);
size_t	count(const int *line, const int width, int c);
size_t	count_col(const int *col, const int width, const int height, int c);
size_t	count_players(t_map *map);
int		check_for_invalid_characters(t_map *map);
int		validate_map(t_map *map);
int		validate_line(int *line, int width);
void	register_player_pos(t_vars *vars, t_map *map);

#endif
