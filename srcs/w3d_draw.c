/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:51:19 by oouklich          #+#    #+#             */
/*   Updated: 2019/12/28 22:11:21 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

static int	w3d_darker(int color, float ratio)
{
	int	r;
	int	g;
	int	b;

	r = (int)((color >> 16 & 0xFF) * ratio);
	g = (int)((color >> 8 & 0xFF) * ratio);
	b = (int)((color & 0xFF) * ratio);
	return (r << 16 | g << 8 | b);
}

static void	*w3d_process(t_thread *p)
{
	t_rcast		r;
	int			x;
	int			y;

	x = (p->x_x * WIDTH / NBTHREAD) - 1;
	while (++x < (p->x_x + 1) * WIDTH / NBTHREAD)
	{
		r = w3d_raycaster(p->w, x);
		y = r.ext.x - 1;
		while (++y < r.ext.y && y < HEIGHT)
		{
			r.txt.y = y + (r.line / 2) - (HEIGHT / 2);
			r.txt.y = HEIGHT_TXT * r.txt.y / r.line;
			r.color = p->w->txt.buf[r.txt_idx][HEIGHT_TXT * r.txt.y + r.txt.x];
			r.color = w3d_darker(r.color, r.side);
			p->w->pixels[x + WIDTH * y] = r.color;
		}
		if (r.ext.x > 0 && r.sky < HEIGHT)
			p->w->pixels[x + WIDTH * r.sky] = 0xFFFFFF;
		if (r.ext.y < HEIGHT && (y = r.ext.y - 1) < HEIGHT)
			while (++y < HEIGHT)
				p->w->pixels[x + WIDTH * y] = 0x123456;
	}
	pthread_exit(NULL);
}

void		w3d_thread(t_wolf3d *w)
{
	t_thread	t[NBTHREAD];
	pthread_t	p[NBTHREAD];
	int			i;

	i = -1;
	while (++i < NBTHREAD)
	{
		t[i].x_x = i;
		t[i].w = w;
		t[i].pos = w->pos;
		t[i].dir = w->dir;
		t[i].plane = w->plane;
		pthread_create(&p[i], NULL, (void*)w3d_process, &t[i]);
	}
	while (--i >= 0)
		pthread_join(p[i], NULL);
}

void		w3d_mini_map(t_wolf3d *p)
{
	int		x;
	int		y;

	x = -1;
	while (++x < p->w_map * 4 && (y = -1))
		while (++y < p->h_map * 4)
		{
			p->m_pixels[y * p->w_map * 4 + x] = 0xAA000000;
			if (p->map[(y / 4) * p->w_map + (x / 4)] == 0)
				p->m_pixels[y * p->w_map * 4 + x] = 0xAAFFFFFF;
			if (x / 4 == (int)p->pos.x && y / 4 == (int)p->pos.y)
				p->m_pixels[y * p->w_map * 4 + x] = 0xAAFF0000;
		}
}

int			w3d_draw(t_wolf3d *p)
{
	bzero(p->pixels, WIDTH * HEIGHT * 4);
	w3d_thread(p);
	w3d_mini_map(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_put_image_to_window(p->mlx, p->win, p->m_img, 0, 0);
	return (1);
}
