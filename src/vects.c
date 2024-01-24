#include "../include/vects.h"

void normalize_vect(t_vect *vect)
{
	vect_div(vect, vect_len(vect));
}

int vect_len(t_vect *vect)
{
	double res;

	res = vect -> x * vect -> x;
	res += vect -> y * vect -> y;
	return sqrt(res);
}

void vect_div(t_vect *vect, float factor)
{
	if (!factor)
		return;
	vect -> x /= factor;
	vect -> y /= factor;
}
