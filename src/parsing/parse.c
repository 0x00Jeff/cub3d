/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/08 18:10:28 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <parse.h>
#include <stdio.h>

int	parser(t_vars *vars, char *file)
{
	t_map	*map;

	map = init_map(file); // TODO : make a destroy map
	if (!map)
		return (-1);
	map -> fd = try_open_file(file, "ber");
	if (map -> fd < 0)
		return (-1);
	if (get_map_parts(map))
		return (-1);
	// TODO : quick fix for now, make vars -> map a ptr and make a free map function!
	vars -> map = *map;
	printf("text[NO] = %s\n", map -> texture[NORTH]);
	printf("text[SO] = %s\n", map -> texture[SOUTH]);
	printf("text[WE] = %s\n", map -> texture[WEST]);
	printf("text[EA] = %s\n", map -> texture[EAST]);
	return (0);
}

size_t get_list_len(char **l)
{
	size_t	size;

	if (!l || !*l)
		return (0);

	size = 0;
	while(l[size])
		size++;
	return (size);
}

int	get_map_parts(t_map *map)
{
	if (!map)
		return (-1);

	if (get_textures(map) < 0)
		return (-1);

	return (0);
}

int		get_textures(t_map *map)
{
	char *line;
	char **ptr;
	int fd;

	fd = map -> fd;
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = 0;
	while (ft_strlen(line))
	{
		ptr = ft_split(line, ' ');
		if (get_list_len(ptr) == 2)
		{ // TODO : handle error otherwise
			if (set_map_texture(map, ptr[0], ft_strdup(ptr[1])) == -1)
			{
				ft_putstr_fd("Failed setting texture!\n", 2);
				puts(ptr[1]);
				free_list(ptr);
				free(line);
				return (-1);
			}
		}
		free_list(ptr);

		free(line);
		line = get_next_line(fd);
		line[ft_strlen(line) - 1] = 0;
	}
	return (0);
}

int set_map_texture(t_map *map, char *text, char *file)
{
	char fd;
	if (!map || !text || !file)
		return (-1);

	// ironic name but sure xd
	fd = try_open_file(file, "png");
	if (fd < 0)
	{
		ft_putstr_fd("failed to open texture!\n", 2);
		return (-1);
	}

	if (!ft_strncmp(text, "NO", 3))
		map -> texture[NORTH] = file;
	else if (!ft_strncmp(text, "SO", 3))
		map -> texture[SOUTH] = file;
	else if (!ft_strncmp(text, "WE", 3))
		map -> texture[WEST] = file;
	else if (!ft_strncmp(text, "EA", 3))
		map -> texture[EAST] = file;
	else
	{
		ft_putstr_fd("Wrong, map direction\n", 2);
		return (-1);
	}
	return (0);
}

int	try_open_file(char *file, char *extension)
{
	if (!file)
		return (-1);
	if (check_extension(file, extension))
	{
		ft_putstr_fd("we only accept .ber files!\n", 2);
		return (-1);
	}
	return (open_file(file));
}

t_map	*init_map(char *file)
{
	t_map	*map;

	if (!file)
		return (NULL);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	return (map);
}

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
