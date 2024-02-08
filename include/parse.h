/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:23:11 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/08 21:11:30 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <libft.h>
# include <structs.h>
int		parser(t_vars *vars, char *file);
int		check_extension(char *name, char *extension);
t_map	*init_map(char *file);
int		try_open_file(char *file, char *extension);
int		open_file(char *file);
int		get_map_parts(t_map *map);
int		get_textures(t_map *map);
int		set_map_texture(t_map *map, char *text, char *file);
int		set_map_colors(t_map *map, char obj, char *lgbt_colors);
size_t	get_list_len(char **l);
int		get_surroundings(t_map *map);
int		validate_lgbt(char *l, char *g, char *b);
int		check_digit_list(char **list);
#endif
