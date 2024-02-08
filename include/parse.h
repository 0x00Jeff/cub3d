/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:23:11 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/07 17:41:14 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <structs.h>

int		parser(char *file, t_vars *vars);
int		check_extension(char *name, char *extension);
t_map	*init_map(char *file);
size_t	get_map_size(t_map *map);
void	get_directions(t_vars *vars, t_map *m);
int		open_file(char *file);
#endif
