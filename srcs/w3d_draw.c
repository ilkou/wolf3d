
#include <wolf3d.h>

int		w3d_putpixel(int *pixels, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixels[y * WIDTH + x] = color;
		return (1);
	}
	return (-1);
}

int		w3d_darker(int color, float ratio)
{
	int	r;
	int	g;
	int	b;

	r = (int)((color >> 16 & 0xFF) * ratio);
	g = (int)((color >> 8 & 0xFF) * ratio);
	b = (int)((color & 0xFF) * ratio);
	return (r << 16 | g << 8 | b);
}
#define texWidth 64
#define texHeight 64
void		*w3d_raycaster(t_thread *p)
{
	int	x;

	x = (p->x_x * WIDTH / NBTHREAD) - 1;
	while (++x < (p->x_x + 1) * WIDTH / NBTHREAD)
	{
	}
	pthread_exit(NULL);
}

void		w3d_thread(t_wolf3d *w)
{
	t_thread	t[NBTHREAD];
	pthread_t	p[NBTHREAD];
	int		i;

	i = -1;
	while (++i < NBTHREAD)
	{
		t[i].x_x = i;
		t[i].w = w;
		t[i].pos = w->pos;
		t[i].dir = w->dir;
		t[i].plane = w->plane;
		pthread_create(&p[i], NULL, (void*)w3d_raycaster, &t[i]);
	}
	while (--i >= 0)
		pthread_join(p[i], NULL);
}

void		w3d_mini_map(t_wolf3d *p)
{
	int	x;
	int	y;

	x = -1;
	while (++x < p->w_map * 4 && (y = -1))
		while (++y < p->h_map * 4)
		{
			p->m_pixels[y * p->w_map * 4 + x] = 0xAA000000;
			if (p->map[(y / 4) * p->w_map + (x / 4)] == 0)
				p->m_pixels[y * p->w_map * 4 + x] = 0xAAFFFFFF;
		}
}

int		w3d_draw(t_wolf3d *p)
{
	bzero(p->pixels, WIDTH * HEIGHT * 4);
	w3d_thread(p);
	w3d_mini_map(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_put_image_to_window(p->mlx, p->win, p->m_img, 0, 0);
	return (1);
}
