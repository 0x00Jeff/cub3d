/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ds_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:23:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 12:53:06 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <structs.h>

void	append_map_node(t_map_data *data, char *line)
{
	t_map_line	*node;

	// TODO: might make this returns an int and test for errors -> ask youssf;
	if (!data)
		return ;
	node = (t_map_line *)malloc(sizeof(t_map_line));
	if (!node)
		return ;
	node->line = line;
	node->len = ft_strlen(line);
	if (node->len > data->width)
		data->width = node->len;
	node->next = NULL;
	ft_lstadd_back(&data->data, node);
}

int	*consume_map(t_map_data *m)
{
	int			*res;
	size_t		i;
	size_t		j;
	t_map_line	*map_line;

	if (!m)
		return (NULL);
	map_line = m->data;
	res = ft_calloc(m->width * m->height, sizeof(int));
	if (!res)
		return (NULL);
	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			res[i * m->width + j] = convert_map_char(map_line->line[j]);
			j++;
		}
		i++;
		map_line = map_line->next;
	}
	return (res);
}

size_t	get_list_len(char **l)
{
	size_t	size;

	if (!l || !*l)
		return (0);
	size = 0;
	while (l[size])
		size++;
	return (size);
}
