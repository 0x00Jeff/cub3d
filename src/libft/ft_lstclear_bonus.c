/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:20:08 by afatimi           #+#    #+#             */
/*   Updated: 2022/10/21 23:05:16 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<libft.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr -> next;
		ft_lstdelone(ptr, del);
		ptr = tmp;
	}
	*lst = NULL;
}
