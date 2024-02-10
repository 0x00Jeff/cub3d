/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:23:11 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/10 20:49:58 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <libft.h>
# include <structs.h>

enum
{
	NORTH_IN_MAP = 69,
	SOUTH_IN_MAP,
	WEST_IN_MAP,
	EAST_IN_MAP
};

typedef struct s_map_data
{
	t_map_line	*data;
	size_t		height;
	size_t		width;
}				t_map_data;

//# define DEBUG
int				parser(t_vars *vars, char *file);
int				check_extension(char *name, char *extension);
t_map			*init_map(char *file);
int				try_open_file(char *file, char *extension);
int				open_file(char *file);
int				get_map_parts(t_map *map);
int				get_textures(t_map *map);
int				set_map_texture(t_map *map, char *text, char *file);
int				set_map_colors(t_map *map, char obj, char *lgbt_colors);
size_t			get_list_len(char **l);
int				get_surroundings(t_map *_map);
int				validate_lgbt(char *_r, char *_g, char *_b);
int				check_digit_list(char **list);
uint32_t		construct_lgbt(char *r, char *g, char *b);
t_map_data		*read_map(t_map *map);
void			append_map_node(t_map_data *data, char *line);
int				*consume_map(t_map_data *m);
int				convert_map_char(char c);
void			display_map(t_map *map);
#endif
