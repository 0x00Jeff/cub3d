/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:05:36 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/08 15:12:03 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<parse.h>

int	check_extension(char *name, char *extension)
{
	char			*ext;

	ext = ft_strrchr(name, '.');
	if (!ext)
		return (1);
	return (ft_strcmp(ext + 1, extension));
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
