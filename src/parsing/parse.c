/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/08 21:18:41 by afatimi          ###   ########.fr       */
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
	map->fd = try_open_file(file, "ber");
	if (map->fd < 0)
		return (-1);
	if (get_map_parts(map))
		return (-1);
	// TODO : quick fix for now, make vars -> map a ptr and make a free map function!
	vars->map = *map;
	printf("text[NO] = %s\n", map->tex[NORTH]);
	printf("text[SO] = %s\n", map->tex[SOUTH]);
	printf("text[WE] = %s\n", map->tex[WEST]);
	printf("text[EA] = %s\n", map->tex[EAST]);
	return (0);
}

size_t	get_list_len(char **l)
{
	size_t	size;

	if (!l || !*l)
		return (0);
	size = 0;
	while (l[size])
		size++;
	return (size);
}

int	get_map_parts(t_map *map)
{
	int res;

	if (!map)
		return (-1);
	res = get_textures(map);
	if (res != 4)
	{
		if (res == -1)
			ft_putstr_fd("Erorr: duplicated texture!\n", 2);
		else
			ft_putstr_fd("Error: Missing textures!\n", 2);
		return (-1);
	}
	res = get_surroundings(map);
	return (0);
}

int get_surroundings(t_map *m)
{
	char	*line;
	char	**ptr;
	int		fd;

	fd = m->fd;
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = 0;
	while (ft_strlen(line))
	{
	//	line[ft_strlen(line) - 1] = 0;
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
		{ // TODO : handle error otherwise
			if (set_map_colors(m, *ptr[0], ptr[1]) == -1)
				return (free_list(ptr), free(line), -1);
		}
		free_list(ptr);
		free(line);
		line = get_next_line(fd);
	}
	return (!!m -> tex[UP] + !!m -> tex[DOWN] + \
			!!m -> tex[RIGHT] + !!m -> tex[LEFT]);

}

int	get_textures(t_map *m)
{
	char	*line;
	char	**ptr;
	int		fd;

	fd = m->fd;
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = 0;
	while (ft_strlen(line))
	{
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
		{ // TODO : handle error otherwise
			if (set_map_texture(m, ptr[0], ft_strdup(ptr[1])) == -1)
				return (free_list(ptr), free(line), -1);
		}
		free_list(ptr);
		free(line);
		line = get_next_line(fd);
		line[ft_strlen(line) - 1] = 0;
	}
	return (!!m -> tex[UP] + !!m -> tex[DOWN] + \
			!!m -> tex[RIGHT] + !!m -> tex[LEFT]);
}

uint32_t construct_lgbt(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}

int	set_map_colors(t_map *map, char obj, char *lgbt_colors)
{
	int *where;
	char **ptr;

	where = NULL;
	if (!lgbt_colors)
		return (-1);
	if (obj == 'F')
		where = &map -> floor_color;
	else if (obj == 'C')
		where = &map -> celing_color;
	else
	{
		ft_putstr_fd("Error: invalid objects!\n", 2);
		return (-1);
	}

	ptr = ft_split(lgbt_colors, ',');
	puts(lgbt_colors);
	printf("list len = %ld\n", get_list_len(ptr));
	if (!ptr || get_list_len(ptr) != 3)
	{
		ft_putstr_fd("Error: list does not have 3 parts\n", 2);
		return (-1);
	}
	if (check_digit_list(ptr))
	{
		ft_putstr_fd("Error: not a digit!\n", 2);
		return (-1);
	}
	if (where)
		*where = construct_lgbt(ft_atoi(ptr[0]), ft_atoi(ptr[1]), ft_atoi(ptr[2]));

	return (0);
}

int	set_map_texture(t_map *map, char *text, char *file)
{
	char	fd;
	char	**texture;

	if (!map || !text || !file)
		return (-1);
	// ironic name but sure xd
	fd = try_open_file(file, "png");
	if (fd < 0)
		return (-1);
	if (!ft_strncmp(text, "NO", 3))
		texture = &map -> tex[NORTH];
	else if (!ft_strncmp(text, "SO", 3))
		texture = &map -> tex[SOUTH];
	else if (!ft_strncmp(text, "WE", 3))
		texture = &map -> tex[WEST];
	else if (!ft_strncmp(text, "EA", 3))
		texture = &map -> tex[EAST];
	else
	{
		ft_putstr_fd("Wrong, map direction\n", 2);
		return (-1);
	}
	if (*texture)
		return -1;
	if (texture)
		*texture = file;
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
