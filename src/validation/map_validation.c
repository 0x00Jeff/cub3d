/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:01:27 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 22:52:17 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <validation.h>

int	validator(t_vars *vars)
{
	t_map	*map;

	map = &vars->map;
	if (check_for_invalid_characters(map))
		return (ft_putstr_fd("Error\nfound weird chars in map!\n", \
			2), 1);
	if (count_players(map) != 1)
		return (ft_putstr_fd("Error\nThere has to be one player on the map\n", \
			2), 1);
	register_player_pos(vars, map);
	if (validate_map(map) == -1)
		return (ft_putstr_fd("Error\nInvalid map\n", \
			2), 1);
	display_map(map);
	return (0);
}

bool is_player(int obj)
{
	return ((obj == SOUTH_IN_MAP) + (obj ==  NORTH_IN_MAP) + (obj ==  WEST_IN_MAP) + (obj ==  EAST_IN_MAP));
}

void register_player_pos(t_vars *vars, t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_player(map->m[i * map->width + j]))
			{
				vars->player.angle = (map->m[i * map->width + j] - EAST_IN_MAP) * 90;
				vars->player.pos = (t_vector){i, j};
				map->m[i * map->width + j] = 0;
				break;
			}
			j++;
		}
		i++;
	}
	printf("player angle = %f\n", vars->player.angle);
	printf("player pos = (%f, %f)\n", vars->player.pos.x, vars->player.pos.y);
}

bool	line_space_or_wall(int *line, size_t width, size_t height)
{
	(void)height;
	return ((count(line, width, WALL) + count(line, width, SPACE_IN_MAP)) == width);
}

bool	col_space_or_wall(int *line, size_t width, size_t height)
{
	return ((count_col(line, width, height, WALL) + count_col(line, width, height, SPACE_IN_MAP)) == height);
}

bool	test_set_horizontal(t_map *map, int *first_line, int *last_line)
{
	size_t	i;

	i = 0;
	while (i < map->height && line_space_or_wall(&map->m[i * map->width], map->width, map->height))
		i++;
	if (i >= map->height)
		return (false);
	*first_line = i;
	i = map->height - 1;
	while (i >= 0 && line_space_or_wall(&map->m[i * map->width], map->width, map->height))
		i--;
	*last_line = i;
	if (*first_line == *last_line)
		return (false);
	return (true);
}

bool	test_set_vertical(t_map *map, int *first_col, int *last_col)
{
	size_t	i;

	i = 0;
	while (i < map->width && col_space_or_wall(&map->m[i], map->width, map->height))
		i++;
	if (i >= map->width)
		return (false);
	*first_col = i;
	i = map->width - 1;
	while (i >= 0 && col_space_or_wall(&map->m[i], map->width, map->height))
		i--;
	*last_col = i;
	if (*first_col == *last_col)
		return (false);
	return (true);
}

bool	zero_or_one(int pt)
{
	return (pt == 1 || pt == 0);
}

bool	check_neighbours_binary(t_map *map, t_ivector pt)
{
	// TODO: add bonus characters
	if (map->m[(pt.y) * map->width + (pt.x)] == WALL)
		return (true);
	if (map->m[(pt.y) * map->width + (pt.x)] == SPACE_IN_MAP)
		return (false);
	if (!zero_or_one(map->m[(pt.y - 1) * map->width + (pt.x)]))
		return (false);
	if (!zero_or_one(map->m[(pt.y + 1) * map->width + (pt.x)]))
		return (false);
	if (!zero_or_one(map->m[(pt.y) * map->width + (pt.x - 1)]))
		return (false);
	if (!zero_or_one(map->m[(pt.y) * map->width + (pt.x + 1)]))
		return (false);
	return (true);
}

bool	test_middle_part(t_map *map, t_ivector start, size_t width, size_t height)
{
	size_t	x;
	size_t	y;

	y = start.y;
	while (y < start.y + height)
	{
		x = start.x;
		printf("before (%zu, %zu) %d ... \n", x, y, map->m[y * map->width + x]);
		while(map->m[y * map->width + x] == SPACE_IN_MAP && x < start.x + width)
		{
			printf("sliding horiztonally over SPACE\n");
			x++;
		}
		while(map->m[y * map->width + x] == WALL && x < start.x + width)
		{
			printf("sliding horiztonally over WALL\n");
			x++;
		}
		while (x < start.x + width)
		{
			printf("checking (%zu, %zu) %d ... ", x, y, map->m[y * map->width + x]);
			if (!check_neighbours_binary(map, (t_ivector){x, y}))
			{
				printf("Failed !\n");
				return (false);
			}
			printf("Passed !\n");
			x++;
		}
		y++;
	}
	return (true);
}

int validate_map(t_map *map)
{
	int		first_line;
	int		last_line;
	int		first_col;
	int		last_col;


	puts("VALIDATING THIS BAD BOY....");
	display_map(map);
	puts("-----------");
	if (!test_set_horizontal(map, &first_line, &last_line))
	{
		printf("HORZ: line (%d, %d)\n", first_line, last_line);
		return (-1);
	}
	printf("line (%d, %d)\n", first_line, last_line);
	if (!test_set_vertical(map, &first_col, &last_col))
	{
		printf("VERT: col (%d, %d)\n", first_col, last_col);
		return (-1);
	}
	printf("col (%d, %d)\n", first_col, last_col);
	if (!test_middle_part(map, (t_ivector){first_col, first_line},
			last_col - first_col + 1, last_line - first_line + 1))
		return (-1);
		
	return (0);
}

