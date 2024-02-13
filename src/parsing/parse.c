/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 19:40:43 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <parse.h>
#include <clean.h>

int	parser(t_vars *vars, char *file)
{
	t_map	*map;

	map = init_map(file);
	if (!map)
		return (-1);
	map->fd = try_open_file(file, "cub");
	if (map->fd < 0)
		return (free(map), -1);
	if (get_map_parts(map))
		return (-1);
	vars->map = *map;
	free(map);
	return (0);
}

int	set_map_texture(t_map *map, char *text, char *file)
{
	char	fd;
	char	**texture;

	if (!map || !text || !file)
		return (-1);
	if (!ft_strncmp(text, "NO", 3))
		texture = &map->tex[NORTH];
	else if (!ft_strncmp(text, "SO", 3))
		texture = &map->tex[SOUTH];
	else if (!ft_strncmp(text, "WE", 3))
		texture = &map->tex[WEST];
	else if (!ft_strncmp(text, "EA", 3))
		texture = &map->tex[EAST];
	else
		return (ft_putstr_fd("Error\nWrong map direction\n", 2), -1);
	fd = try_open_file(file, "png");
	if (fd < 0)
		return (-1);
	if (*texture)
		return (ft_putstr_fd("Error\nDuplicated textures!", 2), -1);
	*texture = ft_strdup(file);
	return (0);
}

int	get_map_parts(t_map *map)
{
	t_map_data	*lst_map;
	int			res;

	if (!map)
		return (-1);
	res = get_map_items(map);
	if (res == -1)
		return (-1);
	//res = get_map_items(map);
	//if (res == -1)
		//return (-1);
	if (check_map_items(map) == -1)
		return (-1);
	lst_map = read_map(map);
	if (!lst_map)
		return (ft_putstr_fd("Error: while reading the map\n", 2), -1);
	map->data = consume_map(lst_map);
	if (map->data == NULL)
		return (ft_putstr_fd("Error: while consuming the map\n", 2), -1);
	map->width = lst_map->width;
	free_lst_map(lst_map);
	return (0);
}

int	convert_map_char(char c)
{
	int	res;

	// TODO: add bonus characters
	res = 0;
	if (c == ' ')
		res = SPACE_IN_MAP;
	else if (c == '0')
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
