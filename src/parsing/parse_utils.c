/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:05:36 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/08 21:10:35 by afatimi          ###   ########.fr       */
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
