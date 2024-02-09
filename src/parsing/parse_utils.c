/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:05:36 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/09 15:55:36 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stdio.h>

int	check_extension(char *name, char *extension)
{
	char	*ext;

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

uint32_t	construct_lgbt(char *_r, char *_g, char *_b)
{
	t_color	col;

	col.r = ft_atoi(_r);
	col.g = ft_atoi(_g);
	col.b = ft_atoi(_b);
	if (validate_lgbt(col, _r, _g, _b) == -1)
		return (ft_putstr_fd("Error: invalid lgbt\n", 2), -1);
	return (col.r << 16 | col.g << 8 | col.b);
}

int	validate_lgbt(t_color col, char *r, char *g, char *b)
{
	if (ft_strlen(r) > 4)
		return (-1);
	if (ft_strlen(g) > 4)
		return (-1);
	if (ft_strlen(b) > 4)
		return (-1);
#ifdef DEBUG
	printf("r = %d\n", col.g);
	printf("g = %d\n", col.r);
	printf("b = %d\n", col.b);
#endif
	if (col.r < 0 || col.r > 0xff)
		return (-1);
	if (col.g < 0 || col.g > 0xff)
		return (-1);
	if (col.b < 0 || col.b > 0xff)
		return (-1);
	return (0);
}
