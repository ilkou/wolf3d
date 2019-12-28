
#include <wolf3d.h>

void	init_rcast(t_help *h, t_wolf3d *p, int x)
{
	h->x_mapped = 2 * x / (double)WIDTH - 1;
	h->ray.x = p->dir.x + p->plane.x * h->x_mapped;
	h->ray.y = p->dir.y + p->plane.y * h->x_mapped;
	h->curr.x = (int)p->pos.x;
	h->curr.y = (int)p->pos.y;
	h->delta.x = fabs(1.0 / h->ray.x);
	h->delta.y = fabs(1.0 / h->ray.y);
	h->step.x = h->ray.x < 0 ? -1 : 1;
	h->next.x = h->ray.x < 0 ? (p->pos.x - h->curr.x) * h->delta.x :
		(h->curr.x + 1.0 - p->pos.x) * h->delta.x;
	h->step.y = h->ray.y < 0 ? -1 : 1;
	h->next.y = h->ray.y < 0 ? (p->pos.y - h->curr.y) * h->delta.y :
		(h->curr.y + 1.0 - p->pos.y) * h->delta.y;
}

void	find_wall(t_help *h, t_rcast *r, t_wolf3d *p)
{
	while (h->curr.x >= 0 && h->curr.x < p->w_map
			&& h->curr.y >= 0 && h->curr.y < p->h_map)
	{
		if (h->next.x < h->next.y)
		{
			h->next.x += h->delta.x;
			h->curr.x += h->step.x;
			r->side = h->ray.x > 0 ? OUEST : EST;
		}
		else
		{
			h->next.y += h->delta.y;
			h->curr.y += h->step.y;
			r->side = h->ray.y > 0 ? NORD : SUD;
		}
		if (p->map[h->curr.x + p->w_map * h->curr.y] != 0)
			break ;
	}
	if (r->side == OUEST || r->side == EST)
		h->dist = (h->curr.x - p->pos.x + (1 - h->step.x) / 2) / h->ray.x;
	else
		h->dist = (h->curr.y - p->pos.y + (1 - h->step.y) / 2) / h->ray.y;
}

t_rcast	w3d_raycaster(t_wolf3d *p, int x)
{
	t_rcast r;
	t_help	h;

	init_rcast(&h, p, x);
	find_wall(&h, &r, p);
	r.line = (int)(HEIGHT / h.dist);
	r.ext.x = -r.line / 2 + HEIGHT / 2;
	r.ext.x = (r.ext.x < 0) ? 0 : r.ext.x;
	r.ext.y = r.line / 2 + HEIGHT / 2;
	r.ext.y	= (r.ext.y >= HEIGHT) ? HEIGHT - 1 : r.ext.y;
	r.txt_idx = p->map[h.curr.x + p->w_map * h.curr.y];
	r.txt_idx = r.txt_idx > 0 && r.txt_idx < TOTAL_TXT ? r.txt_idx : 0;
	if (r.side == OUEST || r.side == EST)
		h.hit_x = p->pos.y + h.dist * h.ray.y;
	else
		h.hit_x = p->pos.x + h.dist * h.ray.x;
	h.hit_x -= floor(h.hit_x);
	r.txt.x = (int)(h.hit_x * (double)(WIDTH_TXT));
	if (r.side == OUEST)
		r.txt.x = WIDTH_TXT - r.txt.x - 1;
	if (r.side == SUD)
		r.txt.x = WIDTH_TXT - r.txt.x - 1;
	r.sky = rand() % r.ext.x;
	return (r);
}
