/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:25:14 by afatimi           #+#    #+#             */
/*   Updated: 2022/10/22 16:14:50 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<string.h>
#include<libft.h>

static int	in_set(char c, char *set)
{
	return (ft_strchr(set, c) != NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start_ptr;
	char	*end_ptr;
	char	*s;

	if (!s1 || !set)
		return (NULL);
	start_ptr = (char *)s1;
	end_ptr = (char *)s1 + ft_strlen(s1);
	s = (char *)set;
	while (in_set(*start_ptr, s) && start_ptr != end_ptr)
		start_ptr++;
	while (in_set(*end_ptr, s) && start_ptr != end_ptr)
		end_ptr--;
	return (ft_substr(start_ptr, 0, end_ptr - start_ptr + 1));
}
