/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:52:00 by oouklich          #+#    #+#             */
/*   Updated: 2019/12/28 23:16:38 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int				w3d_close(t_wolf3d *p)
{
	mlx_destroy_image(p->mlx, p->img);
	mlx_destroy_window(p->mlx, p->win);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static void		w3d_init(t_wolf3d *p, char *file)
{
	p->h_map = 0;
	p->mlx = mlx_init();
	p->pos = (t_vec2d){-1.0, -1.0};
	if (w3d_map(p, file, 0, 0) == -1 && write(1, "error: parser fails\n", 20))
		exit(EXIT_FAILURE);
	if (w3d_load_texture(p) == -1 && write(1, "error: textures fails\n", 22))
		exit(EXIT_FAILURE);
	if (p->pos.x == -1.0 && write(1, "error: need a free space\n", 25))
	{
		free(p->map);
		exit(EXIT_FAILURE);
	}
	p->dir = (t_vec2d){-1.0, 0.0};
	p->plane = (t_vec2d){0.0, 0.66};
	p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, "WOLF3D");
	p->img = mlx_new_image(p->mlx, WIDTH, HEIGHT);
	p->pixels = (int *)mlx_get_data_addr(p->img, &p->bpp, &p->size_line,
			&p->endian);
	p->m_img = mlx_new_image(p->mlx, p->w_map * 4, p->h_map * 4);
	p->m_pixels = (int *)mlx_get_data_addr(p->m_img, &p->bpp, &p->size_line,
			&p->endian);
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
