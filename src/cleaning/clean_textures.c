#include<clean.h>

static void    free_tex(mlx_texture_t *tex)
{
	if (!tex)
		return;
	free(tex->pixels);
	free(tex);
}

void free_textures(mlx_texture_t **textures)
{
	int i;

	i = 0;
	while(i < 4)
		free_tex(textures[i++]);
}

void free_texture_names(char **texture_names)
{
	int i;

	i = 0;
	while(i < 4)
		free(texture_names[i++]);
}
