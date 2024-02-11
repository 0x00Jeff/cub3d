/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 12:33:58 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <parse.h>

int	parser(t_vars *vars, char *file)
{
	t_map	*map;

	map = init_map(file);
	if (!map)
		return (-1);
	map->fd = try_open_file(file, "cub");
	if (map->fd < 0)
		return (-1);
	if (get_map_parts(map))
		return (-1);
	// TODO : ask youssef! quick fix for now, make vars -> map a ptr and make a free map function!
	vars->map = *map;
	// TODO : do I need to destroy the map ptr here ???
	return (0);
}

static void	display_map(t_map *map)
{
	// TODO : delete this function later!!
	int	*content;
	int w, h;
	int i, j;

	content = map->m;
	w = map->width;
	h = map->height;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			printf("%d, ", content[i * w + j]);
			j++;
		}
		i++;
		puts("");
	}
}

int	get_map_parts(t_map *map)
{
	t_map_data	*lst_map;
	int			res;

	if (!map)
		return (-1);
	res = get_map_textures(map);
	if (res == -1)
		return (-1);
	res = get_surroundings(map);
	if (res != 2)
	{
		if (res == -1)
			return (ft_putstr_fd("Erorr: duplicated colors!\n", 2), -1);
		else
			return (ft_putstr_fd("Error: Missing colors!\n", 2), -1);
	}
	lst_map = read_map(map);
	if (!lst_map)
		return (ft_putstr_fd("Error: while reading the map\n", 2), -1);
	map->m = consume_map(lst_map);
	if (map->m == NULL)
		return (ft_putstr_fd("Error: while consuming the map\n", 2), -1);
	map->width = lst_map->width;
	display_map(map);
	return (0);
}

int	convert_map_char(char c)
{
	int	res;

	res = 0;
	if (c == ' ' || c == '0')
		res = 0;
	else if (c == '1')
		res = 1;
	else if (c == 'N')
		res = NORTH_IN_MAP;
	else if (c == 'S')
		res = SOUTH_IN_MAP;
	else if (c == 'W')
		res = WEST_IN_MAP;
	else if (c == 'E')
		res = EAST_IN_MAP;
	else
		res = -1;
	return (res);
}

int	get_surroundings(t_map *m)
{
	char	*line;
	char	**ptr;
	int		fd;

	fd = m->fd;
	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	while (line && ft_strlen(line))
	{
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
		{
			if (set_map_colors(m, *ptr[0], ptr[1]) == -1)
				return (ft_putstr_fd("Error\nInvalid Color\n", 2),
					free_list(ptr),
					free(line),
					-1);
		}
		free_list(ptr);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	return (!!m->colors.ceiling_set + !!m->colors.floor_set);
}

int	try_open_file(char *file, char *extension)
{
	if (!file)
		return (-1);
	if (check_extension(file, extension))
	{
		ft_putstr_fd("we only accept .cub files!\n", 2);
		return (-1);
	}
	return (open_file(file));
}
