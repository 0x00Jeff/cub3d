/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:01:27 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 14:25:24 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <validation.h>
#define CRESET "\e[0m"
#define HBLK "\e[0;90m"
#define REDHB "\e[41m"
#define GRNHB "\e[42m"
#define YELHB "\e[43m"

void	display_map_color(t_map *map, int x, int y, char *color)
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
			if (i == y && j == x)
			{
				printf(HBLK"%s", color);
				printf("%d"CRESET, content[i * w + j]);
			}
			else
				printf("%d", content[i * w + j]);
			j++;
		}
		i++;
		puts("");
	}
}

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
	// display_map(map);
	puts("MAP OK !");
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
	# ifdef DEBUG
	printf("player angle = %f\n", vars->player.angle);
	printf("player pos = (%f, %f)\n", vars->player.pos.x, vars->player.pos.y);
	#endif
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
	ll	i;

	i = 0;
	while (i < (ll)map->height && line_space_or_wall(&map->m[i * map->width], map->width, map->height))
		i++;
	if (i >= (ll)map->height)
		return (false);
	*first_line = i;
	i = map->height - 1;
	while (i >= 0 && line_space_or_wall(&map->m[i * map->width], map->width, map->height))
		i--;
	*last_line = i;
	if (*first_line > *last_line)
		return (false);
	return (true);
}

bool	test_set_vertical(t_map *map, int *first_col, int *last_col)
{
	ll	i;

	i = 0;
	while (i < (ll)map->width && col_space_or_wall(&map->m[i], map->width, map->height))
		i++;
	if (i >= (ll)map->width)
		return (false);
	*first_col = i;
	i = map->width - 1;
	while (i >= 0 && col_space_or_wall(&map->m[i], map->width, map->height))
		i--;
	*last_col = i;
	if (*first_col > *last_col)
		return (false);
	return (true);
}

bool	zero_or_one(t_map *map, int x, int y)
{
	int	val;

	if (x < 0 || x >= (ll)map->width)
		return (false);
	if (y < 0 || y >= (ll)map->height)
		return (false);
	val = map->m[y * map->width + x];
	return (val == 1 || val == 0);
}

bool	check_neighbours_binary(t_map *map, t_ivector pt)
{
	// TODO: add bonus characters
	if (map->m[(pt.y) * map->width + (pt.x)] == WALL)
		return (true);
	if (map->m[(pt.y) * map->width + (pt.x)] == SPACE_IN_MAP)
		return (true);
	if (!zero_or_one(map, (pt.x), (pt.y - 1)))
		return (false);
	if (!zero_or_one(map, (pt.x), (pt.y + 1)))
		return (false);
	if (!zero_or_one(map, (pt.x - 1), (pt.y)))
		return (false);
	if (!zero_or_one(map, (pt.x + 1), (pt.y)))
		return (false);
	return (true);
}

#define SLEEP 1000 * 50
bool	test_middle_part(t_map *map, t_ivector start, size_t width, size_t height)
{
	size_t	x;
	size_t	y;

	y = start.y;
	while (y < start.y + height)
	{
		x = start.x;
		// printf("before (%zu, %zu) %d ... \n", x, y, map->m[y * map->width + x]);
		while(map->m[y * map->width + x] == SPACE_IN_MAP && x < start.x + width)
		{
			#ifdef DEBUG
			display_map_color(map, x, y, REDHB);
			printf("sliding horiztonally over SPACE\n");
			usleep(SLEEP);
			system("clear");
			#endif
			x++;
		}
		while(map->m[y * map->width + x] == WALL && x < start.x + width)
		{
			#ifdef DEBUG
			display_map_color(map, x, y, REDHB);
			printf("sliding horiztonally over WALL\n");
			usleep(SLEEP);
			system("clear");
			#endif
			x++;
		}
		while (x < start.x + width)
		{
			#ifdef DEBUG
			display_map_color(map, x, y, YELHB);
			printf("checking (%zu, %zu) %d ... ", x, y, map->m[y * map->width + x]);
			#endif
			if (!check_neighbours_binary(map, (t_ivector){x, y}))
			{
				printf("Failed !\n");
				return (false);
			}
			#ifdef DEBUG
			printf("Passed !\n");
			usleep(SLEEP);
			system("clear");
			#endif
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


	if (!test_set_horizontal(map, &first_line, &last_line))
		return (-1);
	if (!test_set_vertical(map, &first_col, &last_col))
		return (-1);
	if (!test_middle_part(map, (t_ivector){first_col, first_line},
			last_col - first_col + 1, last_line - first_line + 1))
		return (-1);
	return (0);
}

