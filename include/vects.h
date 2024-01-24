#ifndef VECTS_H
# define VECTS_H
# include <math.h>

typedef struct s_vect
{
	double	x;
	double	y;
}			t_vect;

void	normalize_vect(t_vect *vect);
int	vect_len(t_vect *vect);
void vect_div(t_vect *vect, float factor);

#endif
