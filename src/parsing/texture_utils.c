/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:27:08 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 20:33:41 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <structs.h>
#include <utils.h>

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
		err_and_exit("Wrong map direction\n");
	fd = try_open_file(file, "png");
	if (fd < 0)
		return (-1);
	if (*texture)
		err_and_exit("Duplicated textures!\n");
	*texture = ft_strdup(file);
	return (0);
}
