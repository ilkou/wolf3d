/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:51:30 by oouklich          #+#    #+#             */
/*   Updated: 2019/12/28 22:39:17 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void		w3d_rot(t_vec2d *dir, t_vec2d *plane, double angle)
{
	double	oldx;

	oldx = dir->x;
	dir->x = dir->x * cos(angle) - dir->y * sin(angle);
	dir->y = oldx * sin(angle) + dir->y * cos(angle);
	oldx = plane->x;
	plane->x = plane->x * cos(angle) - plane->y * sin(angle);
	plane->y = oldx * sin(angle) + plane->y * cos(angle);
}

static void		w3d_move(t_wolf3d *p, t_vec2d next)
{
	if (p->map[(int)next.x + (int)p->pos.y * p->w_map] == 0
			&& next.x >= 0.00001 && (int)next.x < p->w_map)
		p->pos.x = next.x;
	if (p->map[(int)p->pos.x + p->w_map * (int)next.y] == 0
			&& next.y >= 0.00001 && (int)next.y < p->h_map)
		p->pos.y = next.y;
}

int				w3d_keys(int key, t_wolf3d *p)
{
	t_vec2d next;

	if (key == K_ESC)
		w3d_close(p);
	if (key == K_AR_U)
	{
		next.x = p->pos.x + p->dir.x * 0.25;
		next.y = p->pos.y + p->dir.y * 0.25;
		w3d_move(p, next);
	}
	if (key == K_AR_D)
	{
		next.x = p->pos.x - p->dir.x * 0.25;
		next.y = p->pos.y - p->dir.y * 0.25;
		w3d_move(p, next);
	}
	if (key == K_AR_R)
		w3d_rot(&p->dir, &p->plane, 10.0 * M_PI / 180.0);
	if (key == K_AR_L)
		w3d_rot(&p->dir, &p->plane, -10.0 * M_PI / 180.0);
	if (key == K_AR_U || key == K_AR_D || key == K_AR_R || key == K_AR_L)
		w3d_draw(p);
	return (1);
}
