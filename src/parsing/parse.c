/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/10 23:58:10 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <parse.h>
#include <stdio.h>
#include <stdlib.h>

int	parser(t_vars *vars, char *file)
{
	t_map	*map;

	map = init_map(file); // TODO : make a destroy map
	if (!map)
		return (-1);
	map->fd = try_open_file(file, "cub");
	if (map->fd < 0)
		return (-1);
	if (get_map_parts(map))
		return (-1);
	// TODO : quick fix for now, make vars -> map a ptr and make a free map function!
	vars->map = *map;
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

void	display_map(t_map *map)
{
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
	res = get_textures(map);
	// TODO : make an error function!
	if (res != 4)
	{
		if (res == -1)
			ft_putstr_fd("Erorr: duplicated texture!\n", 2);
		else
			ft_putstr_fd("Error: Missing textures!\n", 2);
		return (-1);
	}
	res = get_surroundings(map);
	if (res != 2)
	{
		if (res == -1)
			ft_putstr_fd("Erorr: duplicated colors!\n", 2);
		else
			ft_putstr_fd("Error: Missing colors!\n", 2);
		return (-1);
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

int	*consume_map(t_map_data *m)
{
	int			*res;
	size_t		i;
	size_t		j;
	t_map_line	*map_line;

	if (!m)
		return (NULL);
	map_line = m->data;
	res = ft_calloc(m->width * m->height, sizeof(int));
	if (!res)
		return (NULL);
	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			res[i * m->width + j] = convert_map_char(map_line->line[j]);
			j++;
		}
		i++;
		map_line = map_line->next;
	}
	return (res);
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
	while (line && ft_strlen(line))
	{
		append_map_node(map_data, line);
		i++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	map->height = i;
	map_data->height = i;
	return (map_data);
}

// TODO: make this returns an int and test for errors
void	append_map_node(t_map_data *data, char *line)
{
	t_map_line	*node;

	if (!data)
		return ;
	node = (t_map_line *)malloc(sizeof(t_map_line));
	if (!node)
		return ;
	node->line = line;
	node->len = ft_strlen(line);
	if (node->len > data->width)
		data->width = node->len;
	node->next = NULL;
	ft_lstadd_back(&data->data, node);
}

int	get_surroundings(t_map *m)
{
	char	*line;
	char	**ptr;
	int		fd;
	int		debug_color;

	fd = m->fd;
	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	while (line && ft_strlen(line))
	{
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
		{
			// TODO : might get rid of this
			debug_color = set_map_colors(m, *ptr[0], ptr[1]);
			if (debug_color == -1)
				return (ft_putstr_fd("Error\nInvalid Color\n", 2),
						free_list(ptr),
						free(line),
						-1);
		}
		free_list(ptr);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break;
		line[ft_strlen(line) - 1] = 0;
	}
	return (!!m->colors.ceiling_set + !!m->colors.floor_set);
}

int	get_textures(t_map *m)
{
	char		*line;
	char		**ptr;
	const int	fd = m -> fd;

	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	while (line && ft_strlen(line))
	{
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
			if (set_map_texture(m, ptr[0], ft_strdup(ptr[1])) == -1)
				return (free_list(ptr), free(line), -1);
		free_list(ptr);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	return (!!m->tex[UP] + !!m->tex[DOWN]
		+ !!m->tex[RIGHT] + !!m->tex[LEFT]);
}

int	set_map_colors(t_map *map, char obj, char *lgbt_colors)
{
	int		*where;
	int		*flag;
	char	**ptr;

	if (!map || !lgbt_colors)
		return (-1);
	if (obj == 'F')
	{
		where = &map->colors.floor;
		flag = &map->colors.floor_set;
	}
	else if (obj == 'C')
	{
		where = &map->colors.ceiling;
		flag = &map->colors.ceiling_set;
	}
	else
		return (ft_putstr_fd("Error: invalid objects!\n", 2), -1);
	ptr = ft_split(lgbt_colors, ',');
	if (!ptr || get_list_len(ptr) != 3)
		return (ft_putstr_fd("Error: list does not have 3 parts\n", 2), -1);
	if (check_digit_list(ptr))
		return (ft_putstr_fd("Error: not a digit!\n", 2), -1);
	if (*where)
		return (ft_putstr_fd("Error, duplicated colors!\n", 2), -1);
	*where = construct_lgbt(ptr[0], ptr[1], ptr[2]);
	if (*where != -1)
		*flag = 1;
	return (free_list(ptr), *where);
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
		return (ft_putstr_fd("Error: Wrong map direction\n", 2), -1);
	fd = try_open_file(file, "png");
	if (fd < 0 || *texture)
		return (-1);
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
		ft_putstr_fd("we only accept .cub files!\n", 2);
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
	map->colors.floor_set = 0;
	map->colors.ceiling_set = 0;
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
