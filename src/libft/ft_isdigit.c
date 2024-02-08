/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:47:48 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/08 21:08:41 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnotdigit(int c)
{
	return (c < '0' || c > '9');
}

int	ft_isdigit_string(char *str)
{
	int	res;

	if (!str)
		return (0);
	res = 0;
	while (*str)
		res += ft_isnotdigit(*str++);
	return (res);
}
