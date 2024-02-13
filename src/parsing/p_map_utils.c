/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:16:48 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 18:16:09 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <structs.h>

int	open_file(char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("open");
	return (fd);
}

t_map	*init_map(char *file)
{
	t_map	*map;

	if (!file)
		return (NULL);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	// TODO : delete the following 2 lines, they're just for debugging a bug
	map->colors.floor = 20;
	map->colors.ceiling = 20;
	map->colors.floor_set = 0;
	map->colors.ceiling_set = 0;
	return (map);
}


int	set_map_colors(t_map *map, char *_obj, char *lgbt_colors)
{
	int		*where;
	int		*flag;
	char	**ptr;
	char	obj;

	if (!map || !lgbt_colors || !_obj)
		return (-1);
	obj = *_obj;
	if (obj == 'F')
		set_where_and_flag(&where, &flag, &map->colors.floor,
			&map->colors.floor_set);
	else if (obj == 'C')
		set_where_and_flag(&where, &flag, &map->colors.ceiling,
			&map->colors.ceiling_set);
	else
		return (ft_putstr_fd("Error: invalid objects!\n", 2), -1);
	if (*flag)
		return (ft_putstr_fd("duplicated colors\n!", 2), -1);
	ptr = ft_split(lgbt_colors, ',');
	*where = construct_lgbt(ptr[0], ptr[1], ptr[2]);
	*flag = (*where != -1);
	return (free_list(ptr), *where);
}

t_map_data	*read_map(t_map *map)
{
	t_map_data	*map_data;
	char		*line;
	int			fd;
	int			i;

	map_data = (t_map_data *)ft_calloc(1, sizeof(t_map_data));
	if (!map_data)
		return (NULL);
	i = 0;
	fd = map->fd;
	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	if (!ft_strlen(line))
		(free(line), line = NULL);
	while (line && ft_strlen(line))
	{
		append_map_node(map_data, line);
		i++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	free(line);
	map->height = i;
	map_data->height = i;
	return (map_data);
}
