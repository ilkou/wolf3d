#include <wolf3d.h>

void	print_map(t_wolf3d *p)
{
	int i, j = -1;
	while (++j < p->h_map && (i = -1))
	{
		while (++i < p->w_map)
			printf("%c ", p->map[j * p->w_map + i]);
		printf("\n");
	}
}
