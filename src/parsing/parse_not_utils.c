/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_not_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:55:19 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 20:31:39 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <clean.h>
#include <utils.h>

bool	check_textures(t_map *map)
{
	return ((!!map -> tex[SOUTH]
			+ !!map -> tex[NORTH]
			+ !!map -> tex[EAST]
			+ !!map -> tex[WEST]) == 4);
}

bool	check_colors(t_map *map)
{
	return ((map -> colors.ceiling_set
			+ map -> colors.floor_set) == 2);
}

bool map_items_collected(t_map *map)
{
	return (check_textures(map) & check_colors(map));
}

int	check_map_items(t_map *map)
{
	if (!check_textures(map))
		err_and_exit("Textures problem\n");
	if (!check_colors(map))
		err_and_exit("Colors problem\n");
	return (0);
}

static void	free_stuff(char **ptr, char *line)
{
	free_list(ptr);
	free(line);
}

int	item_setter_dispatcher(t_map *m, char *where, char *what)
{
	if (!check_textures(m))
		return set_map_texture(m, where, what);
	else
		return set_map_colors(m, where, what);
}

int	get_map_items(t_map *m)
{
	char		*line;
	char		**ptr;
	const int	fd = m -> fd;

	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	while (line && !map_items_collected(m))
	{
		if (!ft_strlen(line))
		{
			free(line);
			line = get_next_line(fd);
			if (!line)
				break;
			line[ft_strlen(line) - 1] = 0;
			continue;
		}
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
		{
			if (item_setter_dispatcher(m, ptr[0], ptr[1]) == -1)
				err_and_exit("Invalid Color\n");
		}
		free_stuff(ptr, line);
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	if (line)
		free(line);
	return (0);
}
