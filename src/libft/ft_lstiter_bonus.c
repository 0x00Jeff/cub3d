/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:20:29 by afatimi           #+#    #+#             */
/*   Updated: 2022/10/09 12:14:49 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<libft.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	if (!lst || !f)
		return ;
	ptr = lst;
	while (ptr)
	{
		tmp = ptr -> next;
		f(ptr -> content);
		ptr = tmp;
	}
}
