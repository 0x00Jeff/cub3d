
#include<clean.h>

void free_lst_map(t_map_data *ptr)
{
	t_map_line *line;
	t_map_line *tmp;

	line = ptr -> data;

	while(line)
	{
		tmp = line -> next;
		free(line);
		line = tmp;
	}
	free(ptr);
}

void	destroy_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	// TODO : use this function!
	i = 0;
	while (i < 4)
	{
		if (map->tex[i])
		{
			free(map->tex[i]);
			map->tex[i] = NULL;
		}
		i++;
	}
}
