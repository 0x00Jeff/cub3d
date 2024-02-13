
#include<clean.h>

void free_lst_map(t_map_data *ptr)
{
	t_map_line *line;
	t_map_line *tmp;

	line = ptr -> data;

	while(line)
	{
		tmp = line -> next;
		free(line -> line);
		free(line);
		line = tmp;
	}
	free(ptr);
}

void	destroy_map(t_map *map)
{
	(void)map;
	return;
}
