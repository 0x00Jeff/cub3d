/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:53:41 by afatimi           #+#    #+#             */
/*   Updated: 2022/10/08 18:33:23 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<libft.h>

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) | ft_isdigit(c));
}
