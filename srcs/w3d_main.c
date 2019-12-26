
#include <wolf3d.h>

int				w3d_close(t_wolf3d *p)
{
	mlx_destroy_image(p->mlx, p->img);
	mlx_destroy_window(p->mlx, p->win);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static void			w3d_init(t_wolf3d *p, char *file)
{
	p->h_map = 0;
	if (w3d_map(p, file, 0, 0) == -1 && write(1, "error: parsing\n", 15))
		exit(EXIT_FAILURE);
	print_map(p);
    p->pos = (t_vec2d){22.0, 12.0};
    p->dir = (t_vec2d){-1.0, 0.0};
    p->plane = (t_vec2d){0.0, 0.66};
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, "WOLF3D");
	p->img = mlx_new_image(p->mlx, WIDTH, HEIGHT);
	p->pixels = (int *)mlx_get_data_addr(p->img, &p->bpp, &p->size_line, &p->endian);
}

int				main(int argc, char **argv)
{
	t_wolf3d p;

	if (argc != 2 && write(1, "usage: ./wolf3d file\n", 21))
		return (EXIT_FAILURE);
	w3d_init(&p, argv[1]);
	w3d_draw(&p);
	mlx_hook(p.win, 17, (1L << 17), w3d_close, &p);
	mlx_hook(p.win, 2, 0, w3d_keys, &p);
	mlx_loop(p.mlx);
	return (EXIT_SUCCESS);
}
