/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:47:37 by afatimi           #+#    #+#             */
/*   Updated: 2022/11/05 19:31:53 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdlib.h>
#include<libft.h>

size_t	min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*result;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		size = 0;
	else
		size -= start;
	size = min(size, len);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, s + start, size);
	result[size] = 0;
	return (result);
}
