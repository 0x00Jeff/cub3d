/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:48:46 by afatimi           #+#    #+#             */
/*   Updated: 2022/10/08 11:28:49 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<libft.h>

int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	size_t	count;

	ptr = lst;
	if (!ptr)
		return (0);
	count = 1;
	while (ptr -> next)
	{
		ptr = ptr -> next;
		count++;
	}
	return (count);
}
