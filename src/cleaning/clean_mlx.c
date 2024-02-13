#include<clean.h>

void destroy_mlx_image(t_vars *vars)
{
		mlx_close_window(vars->mlx);
}
