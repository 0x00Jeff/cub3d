/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:05:36 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/09 12:28:57 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<parse.h>

int	check_extension(char *name, char *extension)
{
	char			*ext;

	if (!name || !extension)
		return (1);
	ext = ft_strrchr(name, '.');
	if (!ext)
		return (1);
	return (ft_strcmp(ext + 1, extension));
}

int	check_digit_list(char **list)
{
	size_t	index;
	size_t	res;

	res = 0;
	index = 0;
	while (list[index])
		res += ft_isdigit_string(list[index++]);
	return (res);
}

uint32_t	construct_lgbt(uint32_t r, uint32_t g, uint32_t b)
{
	if (validate_lgbt(r, g, b) == -1)
		return (ft_putstr_fd("Error: invalid lbgt\n", 2), (-1));
	return ((uint8_t)r << 16 | (uint8_t)g << 8 | (uint8_t)b);
}

int	validate_lgbt(uint32_t r, uint32_t g, uint32_t b)
{
	if (r < 0 || r > 0xff)
		return (-1);
	if (g < 0 || g > 0xff)
		return (-1);
	if (b < 0 || b > 0xff)
		return (-1);
	return (0);
}
