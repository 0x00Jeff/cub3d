/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_not_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:55:19 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 20:07:13 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

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
	return ((check_textures(map) + check_colors(map)) == 6);
}

int	check_map_items(t_map *map)
{
	if (!check_textures(map))
		return (ft_putstr_fd("Error!\nTextures problem\n", 2), -1);
	if (!check_colors(map))
		return (ft_putstr_fd("Error!\nColors problem\n", 2), -1);
	return (0);
}

static void	free_stuff(char **ptr, char *line)
{
	free_list(ptr);
	free(line);
}

int	get_map_items(t_map *m, int (*item_setter)(t_map *, char *, char *))
{
	char		*line;
	char		**ptr;
	const int	fd = m -> fd;

	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	while (line /*&& ft_strlen(line) */&& !map_items_collected(m))
	{
		puts(line);
		if (!ft_strlen(line))
		{
			line = get_next_line(fd);
			continue;
		}
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
		{
			if (item_setter(m, ptr[0], ptr[1]) == -1)
				return (ft_putstr_fd("Error\nInvalid Color\n", 2),
					free_stuff(ptr, line), -1);
		}
		free_stuff(ptr, line);
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	return (0);
}
